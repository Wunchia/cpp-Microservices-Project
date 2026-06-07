#include "CryptoUtil.h"
#include "common.h"
#include "error_pages.h"
#include "success_pages.h"
#include <fcntl.h>
#include <wfrest/HttpMsg.h>
#include <wfrest/HttpServer.h>
#include <workflow/MySQLMessage.h>
#include <workflow/WFHttpServer.h>
#include <workflow/HttpMessage.h>
#include <workflow/MySQLResult.h>
#include <workflow/HttpUtil.h>
#include <workflow/WFTask.h>
#include <workflow/WFTaskFactory.h>
#include <workflow/WFFacilities.h>
#include <workflow/WFGlobal.h>
#include <workflow/Workflow.h>

using namespace std;
using namespace protocol;
using namespace std::placeholders;
using namespace protocol;

//全局常量
static const char* MYSQL_URL="mysql://root:123456@localhost/demo";
static const int MYSQL_RETRY=3;
static const char* STATIC_DIR="resources";
static const char* SERVER_NAME="LoveLanlanServer";

WFFacilities::WaitGroup waitGroup(1);

//===============工具函数===============
//从请求中取出 name 和 password 用map存储
static map<string,string> parse_form(const string& body){
    map<string,string> form;
    size_t key_start=0;
    while(key_start<body.size()){
        size_t eq_pos=body.find('=',key_start);
        size_t amp_pos=body.find('&',eq_pos+1);
        size_t val_end=(amp_pos==string::npos)?body.size():amp_pos;

        string key=body.substr(key_start,eq_pos-key_start);
        string value=body.substr(eq_pos+1,val_end-eq_pos-1);
        form[key]=value;
        key_start=val_end+1;
    }
    return form;
}

//从请求中取出token并进行比较
static string extract_bearer_token(HttpRequest* req){
    HttpHeaderCursor cursor(req);
    string name,value;
    while(cursor.next(name,value)){
        cerr<<"[DEBUG] header: '"<<name<<"' = '"<<value<<"'"<<endl;
        if(name=="Authorization"){
            const string prefix="Bearer ";
            if(value.size()>prefix.size()&&value.compare(0,prefix.size(),prefix)==0){
                return value.substr(prefix.size());
            }
        }
    }
    return "";
}

//===============回调函数===============
void register_mysql_callback(WFMySQLTask* mysqlTask,HttpResponse* resp){
    int state=mysqlTask->get_state();
    if(state!=WFT_STATE_SUCCESS){
        cerr<<WFGlobal::get_error_string(state, mysqlTask->get_error())<<endl;
        return;
    }

    MySQLResponse* mysqlResp=mysqlTask->get_resp();
    int err=mysqlResp->get_error_code();
    if(err==1062){ //用户名重复
        resp->set_status_code("409");
        resp->append_output_body(R_409);
    }else if(err!=0){
        cerr<<"[REGISTER]：MySQL error,errno="<<err<<", msg="
            <<mysqlResp->get_error_msg()<<endl;
        resp->set_status_code("500");
        resp->append_output_body(R_500);
    }else{
        resp->set_status_code("201");
        resp->append_output_body(R_201);
    }
}

void login_mysql_callback(WFMySQLTask* mysqlTask,HttpResponse* resp,const string password){
    int state=mysqlTask->get_state();
    if(state!=WFT_STATE_SUCCESS){
        resp->set_status_code("500");
        resp->append_output_body(R_500);
        return;
    }

    MySQLResultCursor cursor(mysqlTask->get_resp());

    vector<vector<MySQLCell>>rows;
    cursor.fetch_all(rows);

    if(rows.empty()){
        resp->set_status_code("401");
        resp->append_output_body(R_401);
        return;
    }

    string stored_hash=rows[0][0].as_string();//password
    string salt=rows[0][1].as_string();//salt
    int uid=rows[0][2].as_int();//id
    string uname=rows[0][3].as_string();//username

    string computed=CryptoUtil::hash_password(password, salt);
    if(computed!=stored_hash){
        resp->set_status_code("401");
        resp->append_output_body(R_401);
        return;
    }

    //签发Token
    User user{uid,uname,"",""};
    string token=CryptoUtil::generate_token(user);

    resp->set_status_code("200");
    resp->append_output_body(R"({"token":")"+token+R"("})");
}

void pread_callback(WFFileIOTask* preadTask,HttpResponse* resp,string filename){
    //这里已经读完文件了 干点收尾的活
    //--------------获取参数和返回值----------------
    FileIOArgs* args=preadTask->get_args();
    close(args->fd);
    long bytes=preadTask->get_retval();//实际读取的字节数

    //------------判断任务的状态 处理错误------------
    int state=preadTask->get_state();
    if(state!=WFT_STATE_SUCCESS){
        cerr<<WFGlobal::get_error_string(state, preadTask->get_error())<<endl;
        resp->set_status_code("500");
        resp->append_output_body("<html>500 Server Internal Error.</html>");
        return;
    }

    //-----------将文件内容追加到响应体中------------
    resp->add_header_pair("Content-Disposition",R"(attachment;
        filename=)"+filename);
    resp->append_output_body_nocopy(args->buf,bytes);
}

//===============业务句柄===============
static void handle_register(WFHttpTask* httpTask){
    HttpRequest* req=httpTask->get_req();
    HttpResponse* resp=httpTask->get_resp();

    //解析数据 拿到 用户名 和 密码
    const void *body; size_t size;
    string username,password;
    if(req->get_parsed_body(&body,&size)&&size>0){
        auto form=parse_form(string(static_cast<const char*>(body),size));
        username=form["username"];
        password=form["password"];
    }
    //校验参数
    if(username.empty()||password.empty()){
        resp->set_status_code("400");
        resp->append_output_body(R_400);
        return;
    }

    //生成 盐值 和 哈希密码
    string salt=CryptoUtil::generate_salt(8);
    string hashcode=CryptoUtil::hash_password(password, salt);

    //拼 sql 语句
    string sql="INSERT INTO tbl_user (username,password,salt) VALUES ('"
        +username+"','"+hashcode+"','"+salt+"')";

    //创建 MySQL 任务
    WFMySQLTask* mysqlTask=WFTaskFactory::create_mysql_task(
        MYSQL_URL,MYSQL_RETRY,
        bind(register_mysql_callback,_1,resp)
    );
    cout<<"[REGISTER] SQL: "<<sql<<endl;
    mysqlTask->get_req()->set_query(sql);
    series_of(httpTask)->push_back(mysqlTask);
}

static void handle_login(WFHttpTask* httpTask){
    HttpRequest* req=httpTask->get_req();
    HttpResponse*resp=httpTask->get_resp();

    //解析表单
    const void* body;
    size_t size;
    string username,password;
    if(req->get_parsed_body(&body, &size)&&size>0){
        auto form=parse_form(string(static_cast<const char*>(body),size));
        username=form["username"];
        password=form["password"];
    }

    if(username.empty()||password.empty()){
        resp->set_status_code("400");
        resp->append_output_body(R_400);
        return;
    }

    //拼sql
    string sql="SELECT password,salt,id,username FROM tbl_user"
        " WHERE username='"+username+"' AND tomb=0";

    auto* mysqlTask=WFTaskFactory::create_mysql_task(
        MYSQL_URL,MYSQL_RETRY,
        bind(login_mysql_callback,_1,resp,password)
    );

    mysqlTask->get_req()->set_query(sql);
    series_of(httpTask)->push_back(mysqlTask);
}

static void handle_file(WFHttpTask* httpTask){
    HttpRequest* req=httpTask->get_req();
    HttpResponse* resp=httpTask->get_resp();

    //--------------鉴权----------------
    // 1.从Header中提取出Token
    // 2.调用以后函数校验token
    // 3.错误处理 验证失败返回 401
    string token=extract_bearer_token(req);
    User user;
    if(token.empty()||!CryptoUtil::verify_token(token, user)){
        resp->set_status_code("401");
        resp->append_output_body(R_401);
        return;
    }

    //-------------路径映射--------------
    string uri=req->get_request_uri();
    auto pos=uri.find('?');
    string uri_path=(pos!=string::npos)?uri.substr(0,pos):uri;
    string path=uri_path.substr(strlen("/files"));
    if(path=="/"||path.empty()){
        path="/index.html";//展示服务器首页
    }
    path=STATIC_DIR+path;
    //从uri中截取出文件名
    string filename=path.substr(path.find_last_of('/')+1);

    //-------------创建pread任务----------------
    //这里需要打开文件 如果打开失败需要通过响应头返回错误信息
    int fd=open(path.c_str(),O_RDONLY);//以只读方式打开
    if(fd==-1){
        resp->set_status_code("404");
        resp->append_output_body(R_404);
        return;
    }
    //获取文件大小
    struct stat statbuf;
    fstat(fd,&statbuf);
    size_t size=statbuf.st_size;

    char* buf=(char*)malloc(size);
    assert(buf!=NULL&&"buf malloc failed\n");
    httpTask->set_callback([buf](WFHttpTask* httpTask){
        free(buf);
    });
    //创建读文件任务
    WFFileIOTask* preadTask=WFTaskFactory::create_pread_task(
        fd,buf,size,0,bind(pread_callback,_1,resp,filename)
    );

    //-----------将pread任务添加进序列-----------
    series_of(httpTask)->push_back(preadTask);
}

//===============主流程==================
void process(WFHttpTask* httpTask){
    //----------------解析请求------------------
    HttpRequest* req=httpTask->get_req();
    HttpResponse* resp=httpTask->get_resp();
    resp->add_header_pair("Server",SERVER_NAME);
    string method=req->get_method();
    //下载文件应该通过GET方法 下载的文件在uri中给出
    string uri=req->get_request_uri();
    // <scheme>://<authority><path>?<query>#<fragment>
    // get_request_uri给出的请求行中的路径部分 而非完整url
    // 即 <path>?<query>
    auto pos=uri.find('?');
    string path=(pos!=string::npos)?uri.substr(0,pos):uri;


    //路由分发
    if(method=="POST"&&path=="/register"){
        handle_register(httpTask);
    }else if(method=="POST"&&path=="/login"){
        handle_login(httpTask);
    }else if(method=="GET"&&path.find("/files/")==0){
        handle_file(httpTask);
    }else{
        resp->set_status_code("404");
        resp->append_output_body(R_404);
    }
}

void sig_handler(int signo){
    waitGroup.done();
}

//===============程序入口================
int main(int argc,char *argv[]){
    //通过信号结束进程
    signal(SIGINT,sig_handler);

    WFHttpServer server(process);
    if(server.start(8848)==0){
        waitGroup.wait();
        server.stop();
    }else{
        cerr<<"[ERROR]: Server Start Failed."<<endl;
        exit(1);
    }

    return 0;
}

#include <iostream>
#include <string>
#include <workflow/HttpMessage.h>
#include <workflow/MySQLMessage.h>
#include <workflow/MySQLResult.h>
#include <workflow/WFGlobal.h>
#include <workflow/WFTask.h>
#include <workflow/WFTaskFactory.h>
#include <workflow/WFFacilities.h>
#include <workflow/Workflow.h>
#include <workflow/mysql_types.h>

using namespace std;
using namespace protocol;

struct SeriesContext{
    string url;
    size_t size;
    bool success;
};

void mysql_callback(WFMySQLTask* mysqlTask){
    // 1.判断任务状态
    int state=mysqlTask->get_state();
    if(state!=WFT_STATE_SUCCESS){
        cerr<<WFGlobal::get_error_string(state,mysqlTask->get_error())<<endl;
        return;
    }

    // 2.判断返回包的类型
    MySQLResponse* resp=mysqlTask->get_resp();
    if(resp->get_packet_type()==MYSQL_PACKET_ERROR){
        cerr<<"[ERROR]:"<<resp->get_error_code()
            <<" "<<resp->get_error_msg()<<endl;
        return;
    }

    // 3.解析结果集
    SeriesContext* ctx=static_cast<SeriesContext*>(series_of(mysqlTask)->get_context());
    ctx->success=true;

    MySQLResultCursor cursor(resp);
    cout<<"[LOG]：id="<<cursor.get_insert_id()
        <<", row(s): "<<cursor.get_affected_rows()<<endl;

}

void http_callback(WFHttpTask* httpTask)
{
    //1.判断任务的状态
    int state=httpTask->get_state();
    if(state!=WFT_STATE_SUCCESS){
        cerr<<WFGlobal::get_error_string(state,httpTask->get_error())<<endl;
        return;
    }
    //2.获取响应体
    HttpResponse* resp=httpTask->get_resp();
    const void *body;
    size_t size;
    resp->get_parsed_body(&body, &size);

    SeriesContext* ctx=static_cast<SeriesContext*>(series_of(httpTask)->get_context());
    ctx->size=size;

    //[解析响应体]
    //3.创建MySQL任务
    WFMySQLTask* mysqlTask=WFTaskFactory::create_mysql_task(
        "mysql://root:123456@localhost:3306/demo",
        3,
        mysql_callback
    );

    //4.设置MySQL任务的参数
    //string url=static_cast<char*>(httpTask->user_data);
    string sql="INSERT INTO tbl_webpage(url,size) VALUES('"
        +ctx->url+"',"+to_string(size)+")";
    cout<<"[SQL]"<<sql<<endl;

    MySQLRequest* mysql_req=mysqlTask->get_req();
    mysql_req->set_query(sql);

    //mysqlTask->start();//会另起一个SeriesWork,将mysqlTask作为这个序列的第一个任务执行

    //5.将mysqlTask添加到httpTask所在的序列中
    series_of(httpTask)->push_back(mysqlTask);

}


int main(int argc,char *argv[])
{
    //1.校验命令行参数
    if(argc!=2){
        cerr<<"usage: "<<argv[0]<<"<URL>: "<<endl;
        return 1;
    }

    //2.创建HTTP任务
    WFHttpTask* httpTask=WFTaskFactory::create_http_task(
        argv[1],
        3,
        3,
        http_callback
    );

    // 通过 user_data 将 URL 传递给回调函数
    // httpTask->user_data=argv[1];

    //3.设置任务参数
    HttpRequest* req=httpTask->get_req();
    req->add_header_pair("Accept","*/*");
    req->add_header_pair("User-Agent","wget/1.14 (linux-gun)");
    req->add_header_pair("Connection","close");

    HttpResponse* resp=httpTask->get_resp();
    resp->set_size_limit(20*1024*1024);//20M
    httpTask->set_receive_timeout(30*1000);//30s

    //4.创建串行任务流: SeriesWork
    WFFacilities::WaitGroup waitGroup(1);

    SeriesWork* series=Workflow::create_series_work(httpTask,[&waitGroup](const SeriesWork* series){
        SeriesContext*ctx=static_cast<SeriesContext*>(series->get_context());
        if(ctx->success){
            cout<<"SERIES SUCCESS"<<endl;
        }else{
            cout<<"SERIES FAILED"<<endl;
        }
        delete ctx;
        waitGroup.done();
    });

    //设置序列的上下文
    SeriesContext* ctx=new SeriesContext{argv[1],0,false};
    series->set_context(ctx);

    series->start();//启动序列

    //5.让主线程等待序列结束
    waitGroup.wait();

    return 0;
}

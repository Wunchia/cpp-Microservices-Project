#include "common.h"
#include <arpa/inet.h>
#include <cassert>
#include <csignal>
#include <fcntl.h>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <workflow/HttpMessage.h>
#include <workflow/HttpUtil.h>
#include <workflow/WFGlobal.h>
#include <workflow/WFTask.h>
#include <workflow/WFTaskFactory.h>
#include <workflow/WFHttpServer.h>
#include <workflow/WFFacilities.h>
#include <workflow/Workflow.h>

using namespace std;
using namespace protocol;
using namespace std::placeholders;

WFFacilities::WaitGroup waitGroup(1);

void sig_handler(int signo){
    waitGroup.done();
}

void pread_callback(WFFileIOTask* preadTask,HttpResponse* resp,string filename){
    //struct FileIOArgs{
	// int fd;
	// void *buf;
	// size_t count;
	// off_t offset;
	//};

    //1.获取参数和返回值
    FileIOArgs*args=preadTask->get_args();
    close(args->fd);//千万不要忘记关闭文件描述符
    long bytes=preadTask->get_retval();//获取实际读取的字节数

    //2.判断任务的状态
    int state=preadTask->get_state();
    if(state!=WFT_STATE_SUCCESS){
        cerr<<WFGlobal::get_error_string(state, preadTask->get_error())<<endl;
        resp->set_status_code("500");
        resp->append_output_body("<html>500 Server Internal Error.</html>");
        return;
    }

    //3.将文件内容(buf)追加到响应体中
    // 用nocopy版时需要慎重考虑生命周期
    // 这里要保证 args->buf 的生命周期长于 httpTask
    resp->add_header_pair("Content-Disposition",R"(attachment;
        filename=)"+filename);
    resp->append_output_body_nocopy(args->buf,bytes);
}

// process的工作是 解析请求、分发请求
// 必要时创建任务并push_back进SeriesWork（处理业务逻辑、生成响应）
void process(WFHttpTask* httpTask)
{
    //GET /dir/a.txt HTTP/1.1
    // 1.解析请求
    HttpRequest* req=httpTask->get_req();
    string uri=req->get_request_uri();
    auto pos=uri.find('?');
    string path=uri.substr(0,pos);
    // cout<<"[path]:"<<path<<endl;
    //路径映射
    if(path=="/"){
        path+="index.html";
    }
    path="resources"+path;
    // cout<<"[path]:"<<path<<endl;

    //获取文件名
    string filename=path.substr(path.find_last_of('/')+1);

    //2.创建pread任务
    HttpResponse* resp=httpTask->get_resp();
    resp->add_header_pair("Server","My Workflow Server");

    int fd=open(path.c_str(),O_RDONLY);
    // assert(fd!=-1&&"open failed");
    if (fd == -1) {
        resp->set_status_code("404");
        resp->append_output_body("<html>404 Not Found.</html>");
        return;
    }
    //获取文件的大小
    struct stat statbuf;
    fstat(fd,&statbuf);
    size_t size=statbuf.st_size;
    cout<<"size:"<<size<<endl;

    char* buf=(char*)malloc(size);//buf是 局部指针变量 process后就销毁
    assert(buf!=NULL&&"malloc failed");

    //这里捕获时使用值传递 复制一份指针才能保存到执行 httpTask时
    // 不严谨的简单理解：指针变量 --> 一律值传递
    httpTask->set_callback([buf](WFHttpTask* httpTask){
        //在httpTask的回调函数中释放buf
        free(buf);
    });
    WFFileIOTask* preadTask=WFTaskFactory::create_pread_task(
        fd,buf,size,0,bind(pread_callback,_1,resp,filename));

    //3.将preadTask添加到序列中
    //虽然是push_back 但会添加在httpTask的前面 因为httpTask固定在序列尾
    series_of(httpTask)->push_back(preadTask);
}

int main(){
    //0.注册信号处理函数
    signal(SIGINT, sig_handler);
    //1.创建http服务器
    WFHttpServer server(process);
    //2.启动服务器 绑定通配符地址 监听8848端口
    if(server.start(8848)==0){
        waitGroup.wait();
        server.stop();
    }else{
        cerr<<"ERROR: Server start Failed."<<endl;
        exit(1);
    }

    return 0;
}

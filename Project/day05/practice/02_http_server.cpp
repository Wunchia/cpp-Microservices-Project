#include <iostream>
#include "common.h"
#include <netinet/in.h>
#include <sys/socket.h>
#include <workflow/HttpMessage.h>
#include <workflow/HttpUtil.h>
#include <workflow/WFFacilities.h>
#include <workflow/WFHttpServer.h>
#include <workflow/WFServer.h>
#include <workflow/WFTaskFactory.h>

using namespace std;
using namespace protocol;

void process(WFHttpTask* task){
    // 1.获取客户端的套接字地址
    struct sockaddr_storage addr;
    socklen_t length =sizeof(addr);
    //框架把对端地址填入 addr
    task->get_peer_addr((struct sockaddr*)&addr, &length);

    // 2.解析套接字地址
    char ipstr[128];
    unsigned short port;
    if(addr.ss_family==AF_INET){
        struct sockaddr_in* sin=(struct sockaddr_in*)&addr;
        inet_ntop(AF_INET,&sin->sin_addr,ipstr,128);
        port=ntohs(sin->sin_port);
    }else if(addr.ss_family==AF_INET6){
        struct sockaddr_in6* sin6=(struct sockaddr_in6*)&addr;
        inet_ntop(AF_INET6,&sin6->sin6_addr,ipstr,128);
        port=ntohs(sin6->sin6_port);
    }else{
        strcpy(ipstr,"Unknown address family");
    }
    cout<<"客户端地址："<<ipstr<<":"<<port<<endl;
    // 3.打印请求序号（从0编号）
    long long seq=task->get_task_seq();
    cout<<"请求序号："<<seq<<endl;

    // 4.解析请求
    HttpRequest* req=task->get_req();
    HttpResponse* resp=task->get_resp();

    // 响应行
    resp->set_http_version("HTTP/1.1");
    resp->set_status_code("200");
    resp->set_reason_phrase("OK");

    // 响应头
    resp->add_header_pair("Content-Type","text/html");
    resp->add_header_pair("Server","My WFHttpServer");
    if(seq==9){
        resp->set_header_pair("Connection","close");
    }

    // 响应体
    resp->append_output_body_nocopy("<html>");
    string line;
    line=line+"<p>"+req->get_method()+" "
        +req->get_request_uri()+" "
        +req->get_http_version()+"</p>";
    resp->append_output_body(line);

    // 遍历请求头部
    HttpHeaderCursor cursor(req);
    string name; string value;
    while(cursor.next(name,value)){
        string header="<p>"+name+" : "+value+"</p>";
        resp->append_output_body(header);
    }
    resp->append_output_body_nocopy("</html>");
}

static WFFacilities::WaitGroup waitGroup(1);

void sig_handler(int signo)
{
    waitGroup.done();
}

int main(int argc,char *argv[])
{
    signal(SIGINT,sig_handler);

    WFHttpServer server(process);

    if(server.start(8848)==0){
        waitGroup.wait();
        server.stop();
    }else{
        cerr<<"ERROR: Server start failed!"<<endl;
        exit(1);
    }
    return 0;
}

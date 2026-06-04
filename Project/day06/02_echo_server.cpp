#include <arpa/inet.h>
#include <csignal>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <workflow/HttpMessage.h>
#include <workflow/HttpUtil.h>
#include <workflow/WFTaskFactory.h>
#include <workflow/WFHttpServer.h>
#include <workflow/WFFacilities.h>

using namespace std;
using namespace protocol;

WFFacilities::WaitGroup waitGroup(1);

void sig_handler(int signo){
    waitGroup.done();
}

// process的工作是 解析请求、分发请求
// 必要时创建任务并push_back进SeriesWork（处理业务逻辑、生成响应）
void process(WFHttpTask* task){

    //1.打印套接字地址
    struct sockaddr_storage addr;
    socklen_t length=sizeof(addr);
    task->get_peer_addr((struct sockaddr*)&addr, &length);
    //套接字地址-->IP:Port
    char ipstr[INET6_ADDRSTRLEN];
    unsigned short port;
    if(addr.ss_family==AF_INET){
        //IPv4地址
        struct sockaddr_in* sin=(struct sockaddr_in*)&addr;
        inet_ntop(AF_INET, &sin->sin_addr, ipstr, INET6_ADDRSTRLEN);
        port=ntohs(sin->sin_port);//将网络字节序转换成主机字节序
    }else if(addr.ss_family==AF_INET6){
        //IPv6地址
        struct sockaddr_in6* sin6=(struct sockaddr_in6*)&addr;
        inet_ntop(AF_INET, &sin6->sin6_addr, ipstr, INET6_ADDRSTRLEN);
        port=ntohs(sin6->sin6_port);//将网络字节序转换成主机字节序
    }else{
        strcpy(ipstr,"Unknown");
    }
    //记录日志(这里直接打印出来)
    cout<<"[Client Addr]:"<<ipstr<<" : "<<port<<endl;

    //2.打印请求序号
    long long seq=task->get_task_seq();
    cout<<"[Request Seq]:"<<seq<<endl;

    //3.将收到的请求放入响应体，返回给客户端
    HttpResponse* resp=task->get_resp();
    resp->set_status_code("200");
    resp->add_header_pair("Server","LocalHttpServer");
    resp->add_header_pair("Content-Type","text/html");
    if(seq==9){
        //关闭TCP链接 在应用层的高度怎么关闭tcp
        // close(sock_fd);
        resp->add_header_pair("Connection","close");
    }
    //设置响应体
    //先解析请求
    HttpRequest* req=task->get_req();
    //使用nocopy版 特别小心：变量的生命周期
    resp->append_output_body_nocopy("<html>");//静态存储期限 与天地同寿
    //解析请求行
    string line;//局部变量 自动存储期限 process结束就销毁（用nocopy版会ERROR）
    line=line+"<p>"+req->get_method()+" "
            +req->get_request_uri()+" "
            +req->get_http_version()+"</p>";
    // resp->append_output_body_nocopy(line);//(ERROR)
    resp->append_output_body(line);

    //解析请求头
    HttpHeaderCursor cursor(req);
    string name;string value;
    while(cursor.next(name,value)){
        resp->append_output_body("<p>"+name+" : "+value+"</p>");
    }

    //没有请求体
    resp->append_output_body_nocopy("</html>");

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

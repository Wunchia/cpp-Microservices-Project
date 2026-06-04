#include <csignal>
#include <iostream>
#include <workflow/HttpMessage.h>
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
    HttpResponse* resp=task->get_resp();
    //解析请求
    HttpRequest* req=task->get_req();
    string method=req->get_method();
    string uri=req->get_request_uri();
    // cout<<method<<" - "<<uri<<endl;

    //获取用户输入的路径
    auto pos=uri.find('?');
    string path=uri.substr(0,pos);
    // cout<<"path: "<<path<<endl;

    //分发请求
    // if(method=="POST"){
    //     if(path=="/register"){
    //         do_register();
    //     }else if(path=="/login"){
    //         do_login();
    //     }
    // }

    //分发请求
    if(method=="GET"){
        if(path=="/hello"){
            resp->append_output_body("Hello world\n");
        }else if(path=="/lover"){
            resp->append_output_body("Vincio loves lanlan\n");
        }else{
            resp->set_status_code("404");
            resp->append_output_body("404 Not Found\n");
        }
    }

}


int main(){
    signal(SIGINT, sig_handler);

    WFHttpServer server(process);

    if(server.start(8848)==0){
        waitGroup.wait();
        server.stop();
    }else{
        cerr<<"ERROR: Server start Failed."<<endl;
        exit(1);
    }

    return 0;
}

#include <iostream>
#include <signal.h>
#include <wfrest/HttpServer.h>
#include <workflow/WFFacilities.h>

using namespace std;
using namespace wfrest;

static WFFacilities::WaitGroup waitGroup(1);

void sig_handler(int signum){
    waitGroup.done();
}

int main(int argc,char *argv[])
{
    signal(SIGINT, sig_handler);

    HttpServer server;

    server.GET("/hello",[](const HttpReq*req,HttpResp*resp){
        resp->String("Hello World\n");
    });

    server.POST("/echo",[](const HttpReq*req,HttpResp*resp){
        resp->String(req->body());
    });

    if(server.start(8848)==0){
        server.list_routes();
        waitGroup.wait();
        server.stop();
    }else{
        cerr<<"Error: Server start Failed."<<endl;
        exit(1);
    }
}

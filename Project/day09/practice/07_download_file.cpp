#include <iostream>
#include <signal.h>
#include <wfrest/HttpMsg.h>
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

    server.GET("/download-file1", [](const HttpReq* req, HttpResp* resp){
        resp->File("/home/vincio/test/a.txt");
    });

    server.GET("/download-file2", [](const HttpReq* req, HttpResp* resp){
        resp->File("./a.txt");
    });

    server.GET("/download-file3", [](const HttpReq* req, HttpResp* resp){
        resp->File("./a.txt",6);
    });

    server.GET("/download-file4", [](const HttpReq* req, HttpResp* resp){
        resp->File("./a.txt",6,11);
    });

    if(server.start(8848)==0){
        server.list_routes();
        waitGroup.wait();
        server.stop();
    }else{
        cerr<<"Failed to start server "<<endl;
        exit(1);
    }

    return 0;
}

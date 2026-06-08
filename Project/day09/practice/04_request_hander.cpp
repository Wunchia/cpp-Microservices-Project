#include <iostream>
#include <signal.h>
#include <wfrest/HttpMsg.h>
#include <wfrest/HttpServer.h>
#include <workflow/HttpUtil.h>
#include <workflow/WFFacilities.h>

using namespace std;
using namespace wfrest;
using namespace protocol;

static WFFacilities::WaitGroup waitGroup(1);

void sig_handler(int signum){
    waitGroup.done();
}

int main(int argc,char *argv[])
{
    signal(SIGINT,sig_handler);

    HttpServer server;

    server.POST("/all_headers",[](const HttpReq* req,HttpResp* resp){
        HttpHeaderCursor cursor(req);
        string name;
        string value;
        while(cursor.next(name,value)){
            cout<<name<<" : "<<value<<endl;
        }
    });

    server.POST("/header",[](const HttpReq* req,HttpResp* resp){
        const string& host=req->header("Host");
        const string& contentType=req->header("Content-Type");
        const string& xyz=req->header("xyz");//没这个头会返回空字符串
        cout<<"Host: "<<host<<endl;
        cout<<"Content-Type: "<<contentType<<endl;
        cout<<"xyz: "<<xyz<<endl;
    });

    server.POST("/has_header",[](const HttpReq* req,HttpResp* resp){
        if(req->has_header("Host")){
            cout<<"Host: "<<req->header("Host")<<endl;
        }
        if(req->has_header("xyz")){
            cout<<"xyz: "<<req->header("xyz")<<endl;
        }
    });

    if(server.start(8848)==0){
        server.list_routes();
        waitGroup.wait();
        server.stop();
    }else{
        cerr<<"Error: server start failed."<<endl;
        exit(1);
    }

    return 0;
}

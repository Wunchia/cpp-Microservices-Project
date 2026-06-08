#include <iostream>
#include <signal.h>
#include <wfrest/HttpContent.h>
#include <wfrest/HttpServer.h>
#include <workflow/WFFacilities.h>

using namespace std;
using namespace wfrest;

static WFFacilities::WaitGroup wait_group(1);

void sig_handler(int signum)
{
    wait_group.done();
}

int main(int argc,char *argv[])
{
    signal(SIGINT, sig_handler);

    HttpServer server;

    server.GET("/static/*",[](const HttpReq* req, HttpResp* resp)
    {
        string parent="./resources/";
        string file=req->match_path();
        resp->File(parent + file);
    });


    if(server.start(8848) == 0)
    {
        server.list_routes();
        wait_group.wait();
        server.stop();
    }else{
        cerr<<"ERROR: server start failed"<<endl;
        exit(1);
    }

    return 0;
}

#include <iostream>
#include <signal.h>
#include <wfrest/HttpDef.h>
#include <wfrest/HttpMsg.h>
#include <wfrest/HttpServer.h>
#include <workflow/HttpUtil.h>
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
//==============================================================================
    server.POST("/request_body",[](const HttpReq*req,HttpResp* resp){
        string &body=req->body();
        cout<<body<<endl;
    });
//==============================================================================
    server.POST("/form-urlencoded",[](const HttpReq* req,HttpResp* resp){
        if(req->content_type()!=wfrest::APPLICATION_URLENCODED){
            resp->set_status(HttpStatusBadRequest);
            return;
        }
        map<string,string>& form=req->form_kv();
        for(const auto& [key,value]:form){
            cout<<key<<" : "<<value<<endl;
        }
    });
//==========================================================================
    server.POST("/form-data",[](const HttpReq* req,HttpResp* resp){
        if(req->content_type()!=MULTIPART_FORM_DATA){
            resp->set_status(HttpStatusBadRequest);
            return;
        }
        const Form& formData=req->form();
        for(const auto& [key,file]:formData){
            cout<<"key:"<<key<<endl;
            cout<<"filename:"<<file.first<<endl;
            cout<<"content:"<<file.second<<endl;
        }
    });

    if(server.start(8848)==0){
        server.list_routes();
        waitGroup.wait();
        server.stop();
    }else{
        cerr<<"Error: Server start FAILED!"<<endl;
        exit(1);
    }
    return 0;
}

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
    signal(SIGINT,sig_handler);

    HttpServer server;

    server.GET("/all_queries",[](const HttpReq* req,HttpResp* resp){
        const map<string,string>& all_queries=req->query_list();
        for(const auto&[name,value]:all_queries){
            cout<<name<<" : "<<value<<endl;
        }
    });

    server.GET("/query",[](const HttpReq*req,HttpResp*resp){
        const string& username=req->query("username");
        const string& password=req->query("password");
        //没有info参数时会返回空字符串
        const string& info=req->query("info");
        //验证info为空字符串 不为空字符串会打印以下字段
        assert(info==""&&"info doesn't equal \"\"");
        //设置默认参数 如果没有address参数则返回默认值china
        const string& address=req->default_query("address","china");
        cout<<"username: "<<username
            <<", password: "<<password
            <<", info: "<<info
            <<", address: "<<address<<endl;
    });

    server.GET("/has_query",[](const HttpReq*req,HttpResp*resp){
        cout<<req->query("password")<<endl;
        if(req->has_query("password")){
            cout<<"存在参数password"<<endl;
        }
        if(req->has_query("info")){
            cout<<"存在参数info"<<endl;
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

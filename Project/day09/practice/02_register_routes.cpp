#include <iostream>
#include <signal.h>
#include <sys/wait.h>
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
    signal(SIGINT,sig_handler);

    HttpServer server;

    //静态路由
    server.GET("/user/lanlan",[](const HttpReq* req,HttpResp* resp){
        resp->String("喜乐永随\n");
    });

    //参数路由
    server.GET("/user/{name}",[](const HttpReq* req,HttpResp* resp){
        const string& name=req->param("name");
        cout<<"name: "<<name<<endl;
        resp->set_status(HttpStatusOK);
        resp->String("Hello "+name+"\n");
    });

    //通配符路由
    server.GET("/wildcard/*",[](const HttpReq* req,HttpResp* resp){
        cout<<"match_path:"<<req->match_path()<<endl;
        cout<<"full_path:"<<req->full_path()<<endl;
        cout<<"current_path:"<<req->current_path()<<endl;
    });

    //参数和通配符一起使用
    server.GET("/user/{name}/*",[](const HttpReq* req,HttpResp* resp){
        string name=req->param("name");
        cout<<"name:"<<name<<endl;
        cout<<"match_path:"<<req->match_path()<<endl;
        cout<<"full_path:"<<req->full_path()<<endl;
        cout<<"current_path:"<<req->current_path()<<endl;
    });

    if(server.start(8848)==0){
        server.list_routes();
        waitGroup.wait();
        server.stop();
    }else{
        cerr<<"Error: Server Start Failed!"<<endl;
        exit(1);
    }

    return 0;
}

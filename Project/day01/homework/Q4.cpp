#include <iostream>
#include <map>
#include <string>
#include <wfrest/HttpServer.h>
using namespace std;
using namespace wfrest;

int main(int argc,char *argv[])
{
    //创建服务器
    HttpServer server;
    
    //注册路由
    server.GET("/*",[](const HttpReq* req,HttpResp* resp){
        //解析URI
        cout<<"uri: "<<req->get_request_uri()<<endl;
        cout<<"------------------------------"<<endl;
        //解析路径
        cout<<"full_path: "<<req->full_path()<<endl;
        cout<<"match_path: "<<req->match_path()<<endl;
        cout<<"current_path: "<<req->current_path()<<endl;
        cout<<"------------------------------"<<endl;
        //解析查询参数
        const map<string,string>& querys=req->query_list();
        for(const auto&[name,value]:querys){
            cout<<name<<":"<<value<<endl;
        }

    });
    
    //启动服务器
    if(server.start(8888)==0){
        getchar();
        server.stop();
    }else{
        cerr<<"Failed to start server!"<<endl;
        exit(1);
    }
    return 0;
}


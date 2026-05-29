#include <iostream>
#include <wfrest/HttpServer.h>
#include <map>
#include <string>
using std::cout;
using std::endl;
using std::cerr;
using std::map;
using std::string;
using wfrest::HttpServer;
using wfrest::HttpReq;
using wfrest::HttpResp;

int main(int argc,char *argv[])
{
    HttpServer server; 
    server.GET("/*",[](const HttpReq* req,HttpResp*resp) {
        //获取请求
        cout<<"uri: "<<req->get_request_uri()<<endl;
        //解析路径
        cout<<"full_path: "<<req->full_path()<<endl;
        cout<<"match_path: "<<req->match_path()<<endl;
        cout<<"current_path: "<<req->current_path()<<endl;

        //解析查询参数
        const map<string,string>& querys=req->query_list();
        for(const auto&[name,value]:querys){
            cout<<name<<":"<<value<<endl;
        }
    });  

    if(server.start(9527)==0){
        getchar();
        server.stop();
    }else{
        cerr<<"ERROR:Server start failed"<<endl;
        exit(1);
    }
}


#include <iostream>
#include <map>
#include <string>
#include <wfrest/HttpServer.h>
#include <workflow/HttpUtil.h>
using namespace std;
using namespace wfrest;
using namespace protocol;

int main(int argc,char *argv[])
{   //创建服务器
    HttpServer server;

    //注册路由
    server.GET("/api/get",[](const HttpReq* req,HttpResp* resp)->void{
        cout<<"=====解析URI====="<<endl;
        cout<<"uri:"<<req->get_request_uri()<<endl;
        cout<<"full_path:"<<req->full_path()<<endl;
        cout<<"match_path:"<<req->match_path()<<endl;
        cout<<"current_path:"<<req->current_path()<<endl;
        const map<string,string>& querys=req->query_list();
        for(const auto&[key,val]:querys){
            cout<<key<<" : "<<val<<endl;
        }
        cout<<"=====解析请求行====="<<endl;
        cout<<req->get_method()<<" "
            <<req->get_request_uri()<<" "
            <<req->get_http_version()<<endl;
        cout<<"=====解析请求头====="<<endl;
        HttpHeaderCursor cursor(req);
        string name;string value;
        while(cursor.next(name,value)){
            cout<<name<<" : "<<value<<endl;
        }
        cout<<"\r\n";
    });


    server.POST("/api/post",[](const HttpReq* req,HttpResp* resp)->void{
        cout<<"=====解析URI====="<<endl;
        cout<<"uri:"<<req->get_request_uri()<<endl;
        cout<<"full_path:"<<req->full_path()<<endl;
        cout<<"match_path:"<<req->match_path()<<endl;
        cout<<"current_path:"<<req->current_path()<<endl;
        const map<string,string>& querys=req->query_list();
        for(const auto&[key,val]:querys){
            cout<<key<<" : "<<val<<endl;
        }
        cout<<"=====解析请求行====="<<endl;
        cout<<req->get_method()<<" "
            <<req->get_request_uri()<<" "
            <<req->get_http_version()<<endl;
        cout<<"=====解析请求头====="<<endl;
        HttpHeaderCursor cursor(req);
        string name;string value;
        while(cursor.next(name,value)){
            cout<<name<<" : "<<value<<endl;
        }
        cout<<"\r\n";
        cout<<"=====解析请求体====="<<endl;
        const void *body;
        size_t size;
        req->get_parsed_body(&body, &size);
        cout<<string(static_cast<const char*>(body),size)<<endl;
    });

    //启动服务器
    if(server.start(8888)==0){
        getchar();
        server.stop();
    }else{
        cerr<<"Server Start Failed."<<endl;
        exit(1);
    }
    return 0;
}

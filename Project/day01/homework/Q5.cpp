#include <iostream>
#include <map>
#include <string>
#include <wfrest/HttpServer.h>
#include <workflow/HttpUtil.h>
using namespace std;
using namespace wfrest;
using namespace protocol;

int main(int argc,char *argv[])
{
    HttpServer server;

    server.GET("/*",[](const HttpReq* req,HttpResp* resp){
        cout<<"-------请求行-------"<<endl;
        cout<<"method: "<<req->get_method()<<endl;
        cout<<"uri: "<<req->get_request_uri()<<endl;
        cout<<"version: "<<req->get_http_version()<<endl;
        cout<<"-------请求头-------"<<endl;
        HttpHeaderCursor cursor(req);
        string name;string value;
        while(cursor.next(name,value)){
            cout<<name<<":"<<value<<endl;
        }
        cout<<"\r\n";
    });

    server.POST("/*",[](const HttpReq* req,HttpResp* resp){
        cout<<"-------请求行-------"<<endl;
        cout<<"method: "<<req->get_method()<<endl;
        cout<<"uri: "<<req->get_request_uri()<<endl;
        cout<<"version: "<<req->get_http_version()<<endl;
        cout<<"-------请求头-------"<<endl;
        HttpHeaderCursor cursor(req);
        string name;string value;
        while(cursor.next(name,value)){
            cout<<name<<":"<<value<<endl;
        }
        cout<<"\r\n";
        cout<<"-------请求体-------"<<endl;
        cout<<"request body: "<<req->body()<<endl;
        
    });


    if(server.start(8888)==0){
        getchar();
        server.stop();
    }else{
        cerr<<"ERROR:Server start failed"<<endl;
        exit(1);
    }
    
    return 0;
}


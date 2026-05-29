//角色：服务器
//任务：解析Http请求报文
//格式：
//<请求方法><URI><版本>
//<头部字段>
//...
//
//<主体>

#include <wfrest/HttpServer.h>
#include <iostream>
#include <workflow/HttpUtil.h>
using namespace std;
using namespace wfrest;
using namespace protocol;

int main(int argc,char *argv[])
{
    //创建服务器
    HttpServer server;

    //注册路由
    server.GET("/*",[](const HttpReq* req,HttpResp* resp)->void{
        //解析请求行
        cout<<"method: "<<req->get_method()<<" "
            <<"uri: "<<req->get_request_uri()<<" "
            <<"version: "<<req->get_http_version()<<" "
            <<endl;
        //解析请求头
        HttpHeaderCursor cursor(req);
        string name;
        string value;
        while(cursor.next(name,value)){
            cout<<name<<":"<<value<<endl;
        }
        cout<<"\r\n";
    });

    server.POST("/*",[](const HttpReq* req,HttpResp* resp)->void{
        //解析请求行
        cout<<"method: "<<req->get_method()<<" "
            <<"uri: "<<req->get_request_uri()<<" "
            <<"version: "<<req->get_http_version()<<" "
            <<endl;
        //解析请求头
        HttpHeaderCursor cursor(req);
        string name;
        string value;
        while(cursor.next(name,value)){
            cout<<name<<":"<<value<<endl;
        }
        cout<<"\r\n";

        //解析请求体
        //Q:如何解析二进制的body主体
        cout<<"request body: "<<req->body()<<endl;
    });

    //启动服务器
    if(server.start(8888)==0){
        //启动成功
        getchar();
        server.stop();
    }else{
        cerr<<"ERROR:Server start failed"<<endl;
        exit(1);
    }

    return 0;
}


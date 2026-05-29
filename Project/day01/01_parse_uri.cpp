#include <iostream>
#include <map>
#include <string>
using namespace std;
//解析URI
//URI：<scheme>://<authority>/<path>?<query>#<fragment>
//HTTP服务器:
//      绑定通配符地址：0.0.0.0
//      绑定端口：8888
//    

#include <wfrest/HttpServer.h>//包含他就是服务器
using namespace wfrest;

int main(int argc,char *argv[])
{   //1.以默认参数创建HTTP服务器
    HttpServer server; 

    //2.注册路由
    server.GET("/*",[](const HttpReq* req,HttpResp*resp)->void{
        //a.解析请求
        //解析URI: <path>?<query>
        cout<<"uri: "<<req->get_request_uri()<<endl;
        //解析<path>
        //路由：/*
        cout<<"full_path: "<<req->full_path()<<endl;
        //匹配的路径 *号匹配的部分
        cout<<"match_path: "<<req->match_path()<<endl;
        //用户输入的路径  
        cout<<"current_path: "<<req->current_path()<<endl;

        //解析<query>
        const map<string,string>& querys=req->query_list();
        
        //结构化绑定
        for(const auto&[key,value]:querys){
            cout<<key<<":"<<value<<endl;
        }
        //b.处理业务逻辑
        //c.生成响应
        
    });

    //3.启动服务器
    if(server.start(8888)==0){
        //启动成功
        getchar();
        server.stop();
    }else{
        //启动失败
        cerr<<"ERROR:Server start failed"<<endl;
        exit(1);
    }
    return 0;
}


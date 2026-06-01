#include <iostream>
#include <wfrest/HttpMsg.h>
#include <wfrest/HttpServer.h>
using namespace std;
using namespace wfrest;
//重定向
// 301 Move Permanently：永久重定向
// 303 See other：跳转到结果页，第二次请求一定是GET方法
// 307 Temporary Redirect：临时重定向，保持请求方法不变

int main(int argc,char *argv[])
{
    //创建服务器
    HttpServer server;

    //绑定路由
    // ==========================301==============================
    server.GET("/status/301",[](const HttpReq* req,HttpResp* resp){
        resp->set_status(301);
        resp->add_header_pair("Location","/newpage/301");
    });

    server.GET("/newpage/301",[](const HttpReq* req,HttpResp* resp){
        resp->String("<h1>GET newpage/301</h1>");
    });

    //===========================303===============================
    server.GET("/status/303",[](const HttpReq* req,HttpResp* resp){
        resp->set_status(303);
        resp->add_header_pair("Location","/newpage/303");
    });

    server.GET("/newpage/303",[](const HttpReq* req,HttpResp* resp){
        resp->String("<h1>GET newpage/303</h1>");
    });

    server.POST("/status/303",[](const HttpReq*req,HttpResp* resp){
        resp->set_status(303);
        resp->add_header_pair("Location","/newpage/303");
    });

    server.POST("/newpage/303",[](const HttpReq* req,HttpResp* resp){
        resp->String("<h1>POST newpage/303</h1>");
    });

    //============================307=============================
    server.GET("/status/307",[](const HttpReq* req,HttpResp* resp){
        resp->set_status(307);
        resp->add_header_pair("Location","/newpage/307");
    });

    server.GET("/newpage/307",[](const HttpReq* req,HttpResp* resp){
        resp->String("<h1>GET /newpage/307</h1>");
    });

    server.POST("/status/307",[](const HttpReq* req,HttpResp* resp){
        resp->set_status(307);
        resp->add_header_pair("Location","/newpage/307");
    });

    server.POST("/newpage/307",[](const HttpReq* req,HttpResp* resp){
        resp->String("<h1>POST /newpage/307</h1>");
    });

    //启动服务器
    if(server.start(8888)==0){
        server.list_routes();
        getchar();
        server.stop();
    }else{
        cerr<<"Server Start Failed."<<endl;
    }

    return 0;
}

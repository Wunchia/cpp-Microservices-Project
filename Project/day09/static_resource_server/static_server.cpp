#include <iostream>
#include "CryptoUtil.h"
#include "error_pages.h"
#include "success_pages.h"
#include <signal.h>
#include <string>
#include <wfrest/HttpMsg.h>
#include <wfrest/HttpServer.h>
#include <wfrest/PathUtil.h>
#include <workflow/MySQLMessage.h>
#include <workflow/MySQLResult.h>
#include <workflow/WFFacilities.h>
#include <workflow/WFTaskFactory.h>

using namespace std;
using namespace wfrest;
using namespace protocol;

static const char* MYSQL_URL="mysql://root:123456@localhost/demo";
static const int MYSQL_RETRY=3;
static const char* STATIC_DIR="resource";
static const char* SERVER_NAME="LoveLanlanServer";

WFFacilities::WaitGroup waitGroup(1);

void sig_handler(int signum){
    waitGroup.done();
}

void register_handler(const HttpReq*req,HttpResp*resp){

}

void login_handler(const HttpReq*req,HttpResp*resp){

}

void upload_handler(const HttpReq*req,HttpResp*resp){

}

void download_handler(const HttpReq*req,HttpResp*resp){

}

int main(int argc,char *argv[])
{
    signal(SIGINT,sig_handler);

    HttpServer server;

    //注册
    server.POST("/register",register_handler);
    //登录
    server.POST("/login",login_handler);
    //下载
    server.POST("/*",upload_handler);
    //上传
    server.GET("/*",download_handler);

    if(server.start(8848)==0){
        server.list_routes();
        waitGroup.wait();
        server.stop();
    }else{
        cerr<<"[ERROR]: Server Start Failed."<<endl;
        exit(1);
    }

    return 0;
}

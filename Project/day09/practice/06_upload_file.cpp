#include <algorithm>
#include <iostream>
#include <openssl/ssl.h>
#include <signal.h>
#include <wfrest/HttpDef.h>
#include <wfrest/HttpMsg.h>
#include <wfrest/HttpServer.h>
#include <wfrest/PathUtil.h>
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

    server.POST("/upload-file",[](const HttpReq*req,HttpResp*resp){
        if(req->content_type()!=MULTIPART_FORM_DATA){
            resp->set_status(HttpStatusBadRequest);
            return;
        }

        //using Form=map<string , pair<string,string>>
        //                <key ,  file<filename,content>>
        const Form& form=req->form();
        for(const auto& [key,file]:form){
            const string& filename=file.first;
            const string& content=file.second;
#ifdef DEBUG
            cout<<filename<<" : "<<content<<endl;
#endif
            // 用户上传的filename不应该被信任
            // 需要用base转为 basename
            string basename=PathUtil::base(filename);
            resp->Save(basename,std::move(content),"Save"+basename+"Success\n");
        }
    });

    if(server.start(8848)==0){
        server.list_routes();
        waitGroup.wait();
        server.stop();
    }else{
        cerr<<"ERROR: Server start failed."<<endl;
        exit(1);
    }

    return 0;
}

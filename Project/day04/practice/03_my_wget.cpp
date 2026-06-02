#include <iostream>
#include <fstream>
using namespace std;
#include <workflow/WFGlobal.h>
#include <workflow/WFTask.h>
#include <workflow/WFTaskFactory.h> //提供任务工厂
#include <workflow/WFFacilities.h>  //提供线程同步工具
#include <workflow/HttpMessage.h>   //提供httpreq和httpresp
#include <workflow/HttpUtil.h> //提供http解析工具
using namespace protocol;

WFFacilities::WaitGroup waitGroup(1);
string g_output_file;

void http_callback(WFHttpTask* task){
    //检查任务状态
    int state=task->get_state();
    if(state!=WFT_STATE_SUCCESS){
        cerr<<WFGlobal::get_error_string(state, task->get_error())<<endl;
        waitGroup.done();
        return;
    }

    //解析http响应 存入文件
    if(!g_output_file.empty()){
        ofstream ofs(g_output_file,ios::binary);
        if(ofs.is_open()){
            HttpResponse* resp=task->get_resp();
            ofs<<resp->get_http_version()<<" "
               <<resp->get_status_code()<<" "
               <<resp->get_reason_phrase()<<endl;

            HttpHeaderCursor cursor(resp);
            string name; string value;
            while(cursor.next(name,value)){
                ofs<<name<<" : "<<value<<endl;
            }
            ofs<<"\r\n";

            const void* body;
            size_t size;
            resp->get_parsed_body(&body, &size);
            ofs<<static_cast<const char*>(body)<<endl;

            ofs.close();
            waitGroup.done();

        }else{
            cerr<<"Failed to open file:"<<g_output_file<<endl;
            waitGroup.done();
        }
    }
}

int main(int argc,char *argv[])
{
    if(argc!=3){
        cerr<<"Params Wrong!"<<endl;
        exit(1);
    }

    g_output_file=argv[2];

    // 创建任务
    WFHttpTask* task=WFTaskFactory::create_http_task(
        argv[1],
        3,
        3,
        http_callback
    );

    // 设置任务参数
    HttpRequest* req=task->get_req();
    req->set_method("GET");

    // 启动任务
    task->start();

    // 等待任务结束
    waitGroup.wait();

    return 0;
}

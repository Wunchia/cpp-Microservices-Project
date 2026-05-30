#include <iostream>
#include <wfrest/HttpServer.h>
#include <workflow/HttpUtil.h>
#include <workflow/WFTask.h>
#include <workflow/WFTaskFactory.h>
using namespace std;
using namespace wfrest;
using namespace protocol;

void http_callback(WFHttpTask* task)
{
    int state=task->get_state();
    //判断是否成功
    if(state!=WFT_STATE_SUCCESS){
        cerr<<"HTTP request failed: "<<task->get_error()<<endl;
        return;
    }

    HttpResponse* resp=task->get_resp();

    //解析响应行
    cout<<resp->get_http_version()<<" "
        <<resp->get_status_code()<<" "
        <<resp->get_reason_phrase()<<endl;

    //解析响应头
    HttpHeaderCursor cursor(resp);
    string name;string value;
    while(cursor.next(name,value)){
        cout<<name<<" : "<<value<<endl;
    }
    cout<<"\r\n";

    //解析响应体
    const void* body;
    size_t size;
    resp->get_parsed_body(&body,&size);
    cout<<static_cast<const char*>(body)<<endl;
}

int main(int argc,char *argv[])
{   //创建HTTP任务
    WFHttpTask* task=WFTaskFactory::create_http_task(
        "http://www.baidu.com",
        3, //redirect_max
        3, //retry_max
        http_callback
    );

    //设置参数
    //不设置的话会有默认参数

    //提交任务
    task->start();

    getchar();

    return 0;
}

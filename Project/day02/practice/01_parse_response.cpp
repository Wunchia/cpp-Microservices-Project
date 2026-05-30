#include <iostream>
#include <workflow/HttpMessage.h>
#include <workflow/HttpUtil.h>
#include <workflow/WFTask.h>
#include <workflow/WFTaskFactory.h>
using namespace std;
using namespace protocol;

void http_callback(WFHttpTask* task){
    int state=task->get_state();
    if(state!=WFT_STATE_SUCCESS){
        cerr<<WFGlobal::get_error_string(state,task->get_error())<<endl;
        return;
    }

    HttpResponse* resp=task->get_resp();
    cout<<resp->get_http_version()<<" "
        <<resp->get_status_code()<<" "
        <<resp->get_reason_phrase()<<endl;

    HttpHeaderCursor cursor(resp);
    string name;
    string value;
    while(cursor.next(name,value)){
        cout<<name<<" : "<<value<<endl;
    }
    cout<<"\r\n";

    const void *body;
    size_t size;
    resp->get_parsed_body(&body, &size);
    cout<<static_cast<const char*>(body)<<endl;

}

int main(int argc,char *argv[])
{
    WFHttpTask* task=WFTaskFactory::create_http_task(
        "http://stu.cskaoyan.com",
        3,
        3,
        http_callback
    );

    task->start();

    getchar();
    return 0;
}

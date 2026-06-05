#include <cstddef>
#include <iostream>
#include <wfrest/HttpMsg.h>
#include <workflow/HttpMessage.h>
#include <workflow/HttpUtil.h>
#include <workflow/WFFacilities.h>
#include <workflow/WFGlobal.h>
#include <workflow/WFGraphTask.h>
#include <workflow/WFTask.h>
#include <workflow/WFTaskFactory.h>
#include <workflow/Workflow.h>

using namespace std;
using namespace protocol;

void timer_callback(WFTimerTask* timerTask){
    cout<<"Timer triggered."<<endl;
}

void http_callback(WFHttpTask* httpTask){
    cout<<endl<<"=========================="<<endl<<"http"<<endl<<"============================"<<endl;
    int state=httpTask->get_state();
    if(state!=WFT_STATE_SUCCESS){
        cerr<<WFGlobal::get_error_string(state, httpTask->get_error())<<endl;
        exit(1);
    }
    HttpRequest* req=httpTask->get_req();
    cout<<req->get_request_uri()<<": "<<endl;
    HttpResponse* resp=httpTask->get_resp();
    cout<<resp->get_http_version()<<" "<<resp->get_status_code()<<" "<<resp->get_reason_phrase()<<endl;

    HttpHeaderCursor cursor(resp);
    string name;string value;
    while(cursor.next(name,value)){
        cout<<name<<" : "<<value<<endl;
    }

    cout<<"\r\n";

    const void* body;
    size_t* size=static_cast<size_t*>(httpTask->user_data);
    resp->get_parsed_body(&body, size);
    cout<<static_cast<const char*>(body)<<endl;
}


void go_callback(WFHttpTask* http1Task,WFHttpTask* http2Task){
    HttpResponse* resp1=http1Task->get_resp();
    HttpResponse* resp2=http2Task->get_resp();
    cout<<"==========================="<<endl;
    cout<<"========= display ========="<<endl;
    cout<<"==========================="<<endl;
    cout<<"http1 Size:"<<(*static_cast<size_t*>(http1Task->user_data))<<endl;
    cout<<"http2 Size:"<<(*static_cast<size_t*>(http2Task->user_data))<<endl;
    cout<<"Total Size:"<<(*static_cast<size_t*>(http1Task->user_data)+(*static_cast<size_t*>(http2Task->user_data)))<<endl;
}

int main(int argc,char *argv[])
{
    //1.创建4个任务
    WFTimerTask* timer=WFTaskFactory::create_timer_task(3,0,timer_callback);
    WFHttpTask* http1=WFTaskFactory::create_http_task("http://www.pornhub.com",3,3,http_callback);
    WFHttpTask* http2=WFTaskFactory::create_http_task("http://www.baidu.com",3,3,http_callback);
    WFGoTask* display=WFTaskFactory::create_go_task("display",go_callback,http1,http2);

    WFGraphTask* graph=WFTaskFactory::create_graph_task([](WFGraphTask*){
        cout<<"DAG图任务完成"<<endl;
    });

    size_t size1,size2;
    http1->user_data=&size1;
    http2->user_data=&size2;

    //设计模式：Wrapper 装饰者模式 包装器模式
    WFGraphNode& a=graph->create_graph_node(timer);
    WFGraphNode& b=graph->create_graph_node(http1);
    WFGraphNode& c=graph->create_graph_node(http2);
    WFGraphNode& d=graph->create_graph_node(display);

    //定义节点之间的依赖关系
    a-->b-->d;
    a-->c-->d;

    //启动DAG图任务
    graph->start();

    WFFacilities::WaitGroup waitGroup(1);

    Workflow::create_series_work(graph,[&waitGroup](const SeriesWork*){
        waitGroup.done();
    });

    waitGroup.wait();

    return 0;
}

//解析响应报文
// 格式：
// <version> <status> <reason>
// <header>
// ...
//
// <body>
// 角色：HTTP客户端
#include <cstdio>
#include <workflow/HttpMessage.h>
#include <workflow/HttpUtil.h>
#include <workflow/WFTask.h>
#include <workflow/WFTaskFactory.h>
#include <iostream>
using namespace std;
using namespace protocol;

//回调函数中解析响应报文
void http_callback(WFHttpTask* task)
{
    int state=task->get_state();
    //1.判断任务是否成功
    if(state!=WFT_STATE_SUCCESS)
    {   //打印错误信息
        cerr<<WFGlobal::get_error_string(state, task->get_error())<<endl;
        return;
    }

    //2.任务成功（收到HTTP响应）
    HttpResponse* resp=task->get_resp();
    //响应行
    cout<<resp->get_http_version()<<" "
        <<resp->get_status_code()<<" "
        <<resp->get_reason_phrase()<<endl;
    //响应头
    HttpHeaderCursor cursor(resp);
    string name;
    string value;
    while(cursor.next(name,value)){
        //解析头部成功
        cout<<name<<" : "<<value<<endl;
    }
    cout<<"\r\n";
    //响应体
    const void* body;//指向body
    size_t size;//body的大小
    resp->get_parsed_body(&body,&size);

    cout<<static_cast<const char*>(body)<<endl;
    cout<<"Task Done!"<<endl;

}

int main(int argc,char *argv[])
{   //1.创建HTTP任务
    WFHttpTask* task=WFTaskFactory::create_http_task(
        "http://www.google.com", //url
        3, //redirect_max
        3, //retry_max
        http_callback);//回调函数：任务完成后才会执行

    //2.设置参数
    HttpRequest* req=task->get_req();
    req->set_method("GET"); //默认是GET方法
    req->set_request_uri("/"); //默认是"/"

    //3.提交任务，让workflow的线程池异步执行任务
    task->start();
    cout<<"Task Started!"<<endl;
    //4.让主线程阻塞，等待任务执行完成
    getchar();

    // return 0; --> exit(0) --> _exit(0) -->进程退出
}

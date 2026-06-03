#include <iostream>
#include <string>
#include <workflow/HttpMessage.h>
#include <workflow/MySQLMessage.h>
#include <workflow/MySQLResult.h>
#include <workflow/WFTask.h>
#include <workflow/WFTaskFactory.h>
#include <workflow/WFFacilities.h>
#include <workflow/WFGlobal.h>
#include <workflow/Workflow.h>
#include <workflow/mysql_types.h>

using namespace std;
using namespace protocol;

struct SeriesContext{
    string url;
    size_t size;
    bool is_success;
};

void mysql_callback(WFMySQLTask* mysqlTask){
    //处理任务状态出错
    int state=mysqlTask->get_state();
    if(state!=WFT_STATE_SUCCESS){
        cerr<<WFGlobal::get_error_string(state, mysqlTask->get_error())<<endl;
        return;
    }

    //处理数据库返回包的错误信息
    MySQLResponse* resp=mysqlTask->get_resp();
    if(resp->get_packet_type()==MYSQL_PACKET_ERROR){
        cerr<<"[ERROR]:"<<resp->get_error_code()<<" "<<resp->get_error_msg()<<endl;
        return;
    }

    //都没错 则执行成功
    SeriesContext* ctx=static_cast<SeriesContext*>(series_of(mysqlTask)->get_context());
    ctx->is_success=true;

    //解析结果集
    MySQLResultCursor cursor(resp);
    cout<<"[RECORD]: id="<<cursor.get_insert_id()<<", row(s): "<<cursor.get_affected_rows()<<endl;
}

void http_callback(WFHttpTask* httpTask){
    int state=httpTask->get_state();
    if(state!=WFT_STATE_SUCCESS){
        cerr<<WFGlobal::get_error_string(state, httpTask->get_error())<<endl;
        return;
    }

    HttpResponse* http_resp=httpTask->get_resp();
    const void *body;
    size_t size;
    http_resp->get_parsed_body(&body, &size);

    SeriesContext*ctx=static_cast<SeriesContext*>(series_of(httpTask)->get_context());
    ctx->size=size;

    //此时需要写入数据库的数据都已取得，开始创建MySql任务
    WFMySQLTask* mysqlTask=WFTaskFactory::create_mysql_task(
        "mysql://root:123456@localhost:3306/demo",
        3,
        mysql_callback
    );

    string sql="INSERT INTO tbl_webpage(url,size) VALUE('"+ctx->url+"',"+to_string(size)+")";
    MySQLRequest* mysql_req=mysqlTask->get_req();
    mysql_req->set_query(sql);

    series_of(httpTask)->push_back(mysqlTask);
}

int main(int argc,char *argv[])
{
    // 校验命令行参数
    if(argc!=2){
        cerr<<"Params Wrong!"<<endl
            <<"usage: "<<argv[0]<<" <url> "<<endl;
        return 1;
    }

    // 创建HTTP任务
    WFHttpTask* httpTask=WFTaskFactory::create_http_task(
        argv[1],3,3,http_callback
    );

    // 设置任务参数
    HttpRequest* http_req=httpTask->get_req();
    http_req->add_header_pair("Just Try Try","Big Big Hot BooM");
    HttpResponse* http_resp=httpTask->get_resp();
    http_resp->set_size_limit(20*1024*1024);

    httpTask->set_receive_timeout(30*1000);

    // 创建串行任务流
    WFFacilities::WaitGroup waitGroup(1);

    SeriesWork* series=Workflow::create_series_work(httpTask,[&waitGroup](const SeriesWork* series){
        SeriesContext* ctx=static_cast<SeriesContext*>(series->get_context());
        if(ctx->is_success){
            cout<<"SERIES SUCCESS"<<endl;
        }else{
            cout<<"SERIES FAILED"<<endl;
        }
        delete ctx;
        waitGroup.done();//任务流结束后让主线程结束阻塞
    });

    // 设置序列上下文
    SeriesContext* ctx=new SeriesContext{argv[1],0,false};
    series->set_context(ctx);

    // 启动序列
    series->start();

    // 让主线程等待序列结束
    waitGroup.wait();

    return 0;
}

#include <iostream>
#include <string>
#include <workflow/MySQLMessage.h>
#include <workflow/MySQLResult.h>
#include <workflow/WFGlobal.h>
#include <workflow/WFTask.h>
#include <workflow/Workflow.h>
#include <workflow/mysql_types.h>
#include <workflow/WFFacilities.h>
#include <workflow/WFTaskFactory.h>
using namespace std;
using namespace protocol;

WFFacilities::WaitGroup waitGroup(1);

void mysql_callback(WFMySQLTask* task){
    //1.判断任务的状态
    int state=task->get_state();
    if(state!=WFT_STATE_SUCCESS){
        cerr<<WFGlobal::get_error_string(state, task->get_error())<<endl;
        return;
    }

    //2.判断返回包的类型 是错误包则进行错误处理
    MySQLResponse* resp=task->get_resp();
    if(resp->get_packet_type()==MYSQL_PACKET_ERROR){
        cerr<<"error_code: "<<resp->get_error_code()
            <<", error_msg: "<<resp->get_error_msg()<<endl;
        waitGroup.done();
        return;
    }

    //3.处理 DML 结果集
    MySQLResultCursor cursor(resp);
    if(cursor.get_cursor_status()==MYSQL_STATUS_OK){//判断是DML结果集
        unsigned long long rows=cursor.get_affected_rows();
        cout<<rows<<" rows affected"<<endl;
        unsigned long long id=cursor.get_insert_id();
        cout<<"insert id: "<<id<<endl;
        waitGroup.done();
    }
}

int main(int argc,char *argv[])
{   // 1.创建mysql任务
    WFMySQLTask*task=WFTaskFactory::create_mysql_task(
        "mysql://root:123456@localhost:3306/demo",
        3,
        mysql_callback
    );

    // 2.设置任务的参数
    MySQLRequest*req=task->get_req();
    string sql="INSERT INTO tbl_user (username,password,salt) VALUES('Jingtian','1234','very high')";
    req->set_query(sql);

    task->start();

    // SeriesWork* series=Workflow::create_series_work(task,[&waitGroup](const SeriesWork*){
    //     waitGroup.done();
    // });
    // 3.启动任务
    //series->start();

    // 4.等待任务执行完毕
    waitGroup.wait();
    return 0;
}

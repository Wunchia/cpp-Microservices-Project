#include <iostream>
#include <string>
using namespace std;
#include <workflow/WFGlobal.h> //提供全局配置、系统级状态和工具函数 get_error_string
#include <workflow/WFTask.h> //任务控制 WFMySQLTask是其派生类 由WFTaskFactory间接引入
#include <workflow/WFTaskFactory.h> //提供了创建各种异步任务的工厂类
#include <workflow/WFFacilities.h> //提供了线程同步工具 WaitGroup
#include <workflow/MySQLMessage.h>  //提供了MySQLRequest和MySQLResponse的类结构
#include <workflow/mysql_types.h> //提供了MYSQL相关的状态常量和数据类型枚举
#include <workflow/MySQLResult.h> //提供了结果集包装器 游标类 MySQLResultCursor
using namespace protocol;

WFFacilities::WaitGroup waitGroup(1);

void mysql_callback(WFMySQLTask* task){
    // 判断任务状态
    int state=task->get_state();
    if(state!=WFT_STATE_SUCCESS){
        cerr<<WFGlobal::get_error_string(state,task->get_error())<<endl;
        return;
    }

    // 判读返回的包类型 错误处理
    MySQLResponse* resp=task->get_resp();
    if(resp->get_packet_type()==MYSQL_PACKET_ERROR){
        cerr<<"error_code: "<<resp->get_error_code()
            <<", error_msg: "<<resp->get_error_msg()<<endl;
        waitGroup.done();
        return;
    }

    // 处理DML结果集
    MySQLResultCursor cursor(resp);
    if(cursor.get_cursor_status()==MYSQL_STATUS_OK){
        unsigned long long rows=cursor.get_affected_rows();
        cout<<rows<<" rows affected"<<endl;
        unsigned long long id=cursor.get_insert_id();
        cout<<"insert id: "<<id<<endl;
        waitGroup.done();
    }
}

int main(int argc,char *argv[])
{
    // 创建mysql任务
    WFMySQLTask* task=WFTaskFactory::create_mysql_task(
        "mysql://root:123456@localhost:3306/demo",
        3,
        mysql_callback
    );

    // 设置任务参数
    MySQLRequest* req=task->get_req();
    string sql="INSERT INTO tbl_user (username,password,salt) VALUES('Anni','123','very high')";
    req->set_query(sql);

    // 启动任务
    task->start();

    // 等待任务执行完毕
    waitGroup.wait();

    return 0;
}

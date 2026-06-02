#include <iostream>
#include <string>
#include <vector>
using namespace std;
#include <workflow/WFGlobal.h>  //提供全局配置、系统级状态
#include <workflow/WFTaskFactory.h> //提供任务工厂
#include <workflow/WFFacilities.h>  //提供线程同步工具
#include <workflow/MySQLMessage.h>  //提供req和resp
#include <workflow/mysql_types.h>   //提供mysql相关的状态常量
#include <workflow/MySQLResult.h>   //提供结果集包装器cursor
using namespace protocol;

WFFacilities::WaitGroup waitGroup(1);

void display_cell(const MySQLCell& cell){
    if(cell.is_null()){
        cout<<"(NULL)";
    }else if(cell.is_int()){
        cout<<cell.as_int();
    }else if(cell.is_ulonglong()){
        cout<<cell.as_ulonglong();
    }else if(cell.is_float()){
        cout<<cell.as_float();
    }else if(cell.is_double()){
        cout<<cell.as_double();
    }else if(cell.is_string()){
        cout<<cell.as_string();
    }else if(cell.is_date()){
        cout<<cell.as_date();
    }else if(cell.is_time()){
        cout<<cell.as_time();
    }else if(cell.is_datetime()){
        cout<<cell.as_datetime();
    }
}

void mysql_callback(WFMySQLTask* task){
    //判断任务状态
    int state=task->get_state();
    if(state!=WFT_STATE_SUCCESS){
        cerr<<WFGlobal::get_error_string(state,task->get_error())<<endl;
        waitGroup.done();
        return;
    }

    //判断MySql返回包的状态
    MySQLResponse* resp=task->get_resp();
    if(resp->get_packet_type()==MYSQL_PACKET_ERROR){
        cerr<<"error code: "<<resp->get_error_code()
            <<", error msg: "<<resp->get_error_msg()<<endl;
        waitGroup.done();
        return;
    }

    //处理DQL结果集
    MySQLResultCursor cursor(resp);
    if(cursor.get_cursor_status()==MYSQL_STATUS_GET_RESULT){
        cout<<"fields: "<<cursor.get_field_count()<<endl;
        cout<<"rows: "<<cursor.get_rows_count()<<endl;

        vector<MySQLCell> record;
        while(cursor.fetch_row(record)){
            for(const MySQLCell& cell:record){
                display_cell(cell);
                cout<<"\t";
            }
            cout<<endl;
        }
        waitGroup.done();
    }
}

int main(int argc,char *argv[])
{
    //创建MySql任务
    WFMySQLTask* task=WFTaskFactory::create_mysql_task(
        "mysql://root:123456@localhost:3306/demo",
        3,
        mysql_callback
    );

    //设置任务参数
    string sql="SELECT * FROM tbl_user";
    MySQLRequest* req=task->get_req();
    req->set_query(sql);

    task->start();

    waitGroup.wait();
    return 0;
}

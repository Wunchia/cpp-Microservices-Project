#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include <workflow/WFGlobal.h>
#include <workflow/WFTaskFactory.h>
#include <workflow/WFFacilities.h>
#include <workflow/MySQLMessage.h>
#include <workflow/MySQLResult.h>
#include <workflow/mysql_types.h>
using namespace protocol;

WFFacilities::WaitGroup waitGroup(1);

void display_cell(const MySQLCell& cell) {
    if (cell.is_null()) {
        cout << "(NULL)";
    } else if (cell.is_int()) {
        cout << cell.as_int();
    } else if (cell.is_ulonglong()) {
        cout << cell.as_ulonglong();
    } else if (cell.is_float()) {
        cout << cell.as_float();
    } else if (cell.is_double()) {
        cout << cell.as_double();
    } else if (cell.is_string()) {
        cout << cell.as_string();
    } else if (cell.is_date()) {
        cout << cell.as_date();
    } else if (cell.is_time()) {
        cout << cell.as_time();
    } else if (cell.is_datetime()) {
        cout << cell.as_datetime();
    }
}

void insert_callback(WFMySQLTask* task){
    int state=task->get_state();
    if(state!=WFT_STATE_SUCCESS){
        cerr<<WFGlobal::get_error_string(state, task->get_error())<<endl;
        return;
    }

    MySQLResponse* resp=task->get_resp();
    if(resp->get_packet_type()==MYSQL_PACKET_ERROR){
        cerr<<"INSERT SQL error: "
            <<resp->get_error_code()<<"-"
            <<resp->get_error_msg()<<endl;
        return;
    }

    MySQLResultCursor cursor(resp);
    if(cursor.get_cursor_status()==MYSQL_STATUS_OK){
        cout<<"[INSERT]"<<cursor.get_affected_rows()<<" row(s) affected"<<endl;
        cout<<"[INSERT] insert id: "<<cursor.get_insert_id()<<endl;
    }
}

void select_callback(WFMySQLTask* task){
    int state=task->get_state();
    if(state!=WFT_STATE_SUCCESS){
        cerr<<WFGlobal::get_error_string(state,task->get_error())<<endl;
        waitGroup.done();
        return;
    }

    MySQLResponse* resp=task->get_resp();
    if(resp->get_packet_type()==MYSQL_PACKET_ERROR){
        cerr<<"SELECT SQL error:"
            <<resp->get_error_code()<<"-"
            <<resp->get_error_msg()<<endl;
        waitGroup.done();
        return;
    }

    MySQLResultCursor cursor(resp);
    if(cursor.get_cursor_status()==MYSQL_STATUS_GET_RESULT){
        cout<<"\n[SELECT] fields:"<<cursor.get_field_count()
            <<", rows: "<<cursor.get_rows_count()<<endl;
        cout<<"\r\n";
        vector<MySQLCell>record;
        while(cursor.fetch_row(record)){
            for(const MySQLCell& cell:record){
                display_cell(cell);
                cout<<"\t";
            }
            cout<<endl;
        }
    }
    waitGroup.done();
}

int main(int argc,char *argv[])
{
    //==========创建insert任务===========
    WFMySQLTask* insertTask=WFTaskFactory::create_mysql_task(
        "mysql://root:123456@localhost:3306/demo",
        3,
        insert_callback
    );
    insertTask->get_req()->set_query(
        R"(INSERT INTO tbl_user (username,password,salt)
            VALUES ('lili','12345','very hot'))"
    );

    //==========创建select任务============
    WFMySQLTask* selectTask=WFTaskFactory::create_mysql_task(
        "mysql://root:123456@localhost:3306/demo",
        3,
        select_callback
    );

    selectTask->get_req()->set_query(
        "SELECT * FROM tbl_user"
    );

    //============串连任务===========
    SeriesWork* series=Workflow::create_series_work(
        insertTask,
        [](const SeriesWork*){}
    );

    series->push_back(selectTask);

    series->set_callback([](const SeriesWork*){
        cout<<"\n[DONE] INSERT + SELECT finished"<<endl;
        waitGroup.done();
    });

    //===========启动workflow==========
    series->start();
    waitGroup.wait();

    return 0;
}

#include <iostream>
#include <nlohmann/json.hpp>
#include <signal.h>
#include <wfrest/HttpServer.h>
#include <workflow/MySQLResult.h>
#include <workflow/WFFacilities.h>

using namespace std;
using namespace wfrest;
using namespace protocol;
using json=nlohmann::json;

static WFFacilities::WaitGroup waitGroup(1);

void sig_handler(int signum){
    waitGroup.done();
}

int main(int argc,char *argv[])
{
    signal(SIGINT, sig_handler);
    HttpServer server;

    server.GET("/mysql1",[](const HttpReq *req, HttpResp *resp){
        resp->MySQL("mysql://root:123456@localhost:3306","SHOW DATABASES");
    });

    server.GET("/mysql2",[](const HttpReq *req, HttpResp *resp){
        string url="mysql://root:123456@localhost:3306";
        string sql="SHOW DATABASES;USE demo; SELECT * FROM tbl_user";
        resp->MySQL(url,sql);
    });

    server.GET("/mysql3",[](const HttpReq *req, HttpResp *resp){
        string url="mysql://root:123456@localhost:3306";
        string sql="SHOW DATABASES;USE demo1; SELECT * FROM tbl_user";
        resp->MySQL(url,sql,[resp](MySQLResultCursor*cursor){
            cout<<cursor->get_cursor_status()<<endl;

            json result=json::array();
            vector<MySQLCell>record;
            while(cursor->fetch_row(record)){
                result.push_back(record[0].as_string());
            }
            resp->String(result.dump(4));
        });
    });

    if(server.start(8848)==0){
        server.list_routes();
        waitGroup.wait();
        server.stop();
    }else{
        cerr<<"Failed to start server."<<endl;
        exit(1);
    }

    return 0;
}

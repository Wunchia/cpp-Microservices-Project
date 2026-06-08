#include <iostream>
#include <signal.h>
#include <wfrest/HttpMsg.h>
#include <wfrest/HttpServer.h>
#include <workflow/WFFacilities.h>
#include <workflow/WFTask.h>
#include <workflow/WFTaskFactory.h>
#include <workflow/Workflow.h>

using namespace std;
using namespace wfrest;

static WFFacilities::WaitGroup waitGroup(1);

void signal_handler(int signum)
{
    waitGroup.done();
}

int main(int argc,char *argv[])
{
    signal(SIGINT, signal_handler);

    HttpServer server;

    server.GET("/series",[](const HttpReq*req, HttpResp*resp,SeriesWork* series){
        WFTimerTask* timerTask=WFTaskFactory::create_timer_task(
            3,0,[](WFTimerTask*){
                cout<<"定时器任务完成(3秒)"<<endl;
        });

        series->push_back(timerTask);

        resp->String("Hello,SeriesTask!\n");
    });

    if(server.start(8848)== 0){
        server.list_routes();
        waitGroup.wait();
        server.stop();
    }else{
        cerr << "Failed to start server" << endl;
        exit(1);
    }
    return 0;
}

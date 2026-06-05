#include "common.h"
#include <iostream>
#include <workflow/WFFacilities.h>
#include <workflow/WFTask.h>
#include <workflow/WFTaskFactory.h>
#include <workflow/Workflow.h>

using namespace std;

void timer_callback(WFTimerTask* timerTask){
    int state=timerTask->get_state();
    if(state!=WFT_STATE_SUCCESS){
        cout<<"Timer canceled"<<endl;
        return;
    }
    cout<<"Timer Triggered!"<<endl;
    WFTimerTask* next=WFTaskFactory::create_timer_task("timer",1,0,timer_callback);
    series_of(timerTask)->push_back(next);
}

int main(int argc,char *argv[])
{   //1.创建定时器任务
    WFTimerTask* timerTask=WFTaskFactory::create_timer_task("timer",3,0,timer_callback);

    //2.启动定时器任务
    WFFacilities::WaitGroup waitGroup(1);

    SeriesWork* series=Workflow::create_series_work(timerTask,[&waitGroup](const SeriesWork*){
        waitGroup.done();
    });

    series->start();

    sleep(10);
    // series->cancel();

    WFTaskFactory::cancel_by_name("timer");
    waitGroup.wait();

    return 0;
}

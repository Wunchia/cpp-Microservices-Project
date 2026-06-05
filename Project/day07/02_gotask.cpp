#include "common.h"
#include <iostream>
#include <workflow/WFFacilities.h>
#include <workflow/WFTask.h>
#include <workflow/WFTaskFactory.h>
#include <workflow/Workflow.h>

using namespace std;

void add(int a,int b,int &c){
    sleep(3);
    c=a+b;
    cout<<"cal finished"<<endl;
}

int main(int argc,char *argv[])
{
    int a=3;
    int b=4;
    int c=0;
    //1.创建定时器任务
    WFGoTask* goTask=WFTaskFactory::create_go_task("q1",add,a,b,std::ref(c));
    goTask->set_callback([&c](WFGoTask*){
        cout<<"main: c="<<c<<endl;
    });
    //2.启动定时器任务
    WFFacilities::WaitGroup waitGroup(1);

    SeriesWork* series=Workflow::create_series_work(goTask,[&waitGroup](const SeriesWork*){
        waitGroup.done();
    });

    series->start();
    waitGroup.wait();
    return 0;
}

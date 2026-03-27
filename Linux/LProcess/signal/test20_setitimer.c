#include <my_header.h>
void func(int num){
    printf("num : %d\n",num);
}

/*Usage: */
int main(int argc,char *argv[])
{
    signal(SIGALRM,func);

    struct itimerval new_value;//定义定时器参数结构体
    /* it_interval: 设置【周期性】的时间间隔
       即：第一次触发后，每隔多久再次触发？
    */

    //设置重复器
    new_value.it_interval.tv_sec=1;//秒 每隔一秒触发一次
    new_value.it_interval.tv_usec=0;//微秒
    //设置启动器
    new_value.it_value.tv_sec=10;//秒 十秒后第一次响起
    new_value.it_value.tv_usec=0;//微秒

    setitimer(ITIMER_REAL,&new_value,NULL);

    printf("while begin\n");
    while(1);
    printf("while over\n");
    return 0;
}


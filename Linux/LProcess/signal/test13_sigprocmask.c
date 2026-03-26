#include <my_header.h>
void func(int num){
    printf("num : %d\n",num);
}
/*Usage: */
int main(int argc,char *argv[])
{
    signal(2,func);

    sigset_t set,oldset;
    sigemptyset(&set);
    sigaddset(&set,2);
    //全局屏蔽2号信号
    sigprocmask(SIG_BLOCK,&set,&oldset);
    sleep(10);
    printf("sleep over\n");
    //结束对2号信号的屏蔽
    sigprocmask(SIG_UNBLOCK,&set,&oldset);

    printf("while\n");
    while(1);
    return 0;
}


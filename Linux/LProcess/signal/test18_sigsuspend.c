#include <my_header.h>
void func(int num){
    printf("num : %d\n",num);
}

/*Usage: */
int main(int argc,char *argv[])
{
    signal(SIGINT,func);
    sigset_t set,oldset;
    sigemptyset(&set);
    sigaddset(&set,2);

    sigprocmask(SIG_BLOCK,&set,&oldset);
    sleep(10);

    printf("sleep over\n");
    sigset_t mask;
    sigaddset(&mask,3);
    printf("sigsuspend begin\n");
    sigsuspend(&mask);//这里mask会覆盖，变为屏蔽3，放开2

    printf("while begin\n");
    while(1);
    printf("while over\n");
    return 0;
}


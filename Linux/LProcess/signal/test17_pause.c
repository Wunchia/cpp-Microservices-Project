#include <my_header.h>
void func(int num){
    printf("num:%d\n",num);
}
/*Usage: */
int main(int argc,char *argv[])
{
    signal(2,func);

    sigset_t set,oldset;
    sigemptyset(&set);
    sigaddset(&set,2);

    sigprocmask(SIG_BLOCK,&set,&oldset);
    sleep(10);//输入输出 或者不能被打断的代码
    printf("sleep over\n");
    sigprocmask(SIG_UNBLOCK,&set,&oldset);

    printf("pause begin\n");
    pause();
    printf("pause over\n");

    printf("while begin\n");
    while(1);
    printf("while over\n");
    return 0;
}


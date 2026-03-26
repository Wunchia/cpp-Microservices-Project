#include <my_header.h>
void func(int num){
    printf("num:%d\n",num);
    printf("sleep begin\n");
    sleep(10);
    printf("sleep over\n");
}

/*Usage: */
int main(int argc,char *argv[])
{
    struct sigaction act,oldact;
    memset(&act,0,sizeof(act));

    act.sa_handler=func;

    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask,3);
    act.sa_mask=mask;

    sigaction(2,&act,&oldact);

    printf("begin while\n");
    while(1);
    return 0;
}


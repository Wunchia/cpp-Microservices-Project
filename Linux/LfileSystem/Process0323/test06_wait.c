#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    pid_t ret=fork();
    if(ret==0){
        printf("child process.\n");
        sleep(10);
        printf("child process over.\n");
    }else{
        printf("father process.\n");
        sleep(2);
        printf("father process sleep over.\n");
        wait(NULL);//父进程等待子进程执行结束 进行资源回收
        printf("father process over.\n");
    }
    return 0;
}


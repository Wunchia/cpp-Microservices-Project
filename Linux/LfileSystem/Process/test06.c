#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    printf("father process.pid=%d\n",getpid());
    int num=10;
    pid_t ret=fork();
    if(ret==0){
        num=9999;
        printf("child process.pid=%d;num=%d\n",getpid(),num);
    }else{
        printf("father process.pid=%d;num=%d\n",getpid(),num);
    }
    return 0;
}


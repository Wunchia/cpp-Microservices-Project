#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    printf("father process.pid=%d\n",getpid());
    pid_t ret=fork();
    if(ret==0){
        printf("child process.pid=%d\n",getpid());
    }else{
        sleep(30);
        printf("father process.pid=%d\n",getpid());
    }
    return 0;
}


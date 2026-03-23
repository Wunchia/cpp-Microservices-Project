#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    if(fork()==0){
        printf("child process,pid=%d,sid=%d\n",getpid(),getsid(0));
        sleep(10);
    }else{
        printf("father process,pid=%d,sid=%d\n",getpid(),getsid(0));
        sleep(10);
    }
    return 0;
}


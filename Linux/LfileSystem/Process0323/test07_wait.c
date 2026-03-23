#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    pid_t fork_ret=fork();
    if(fork_ret==0){
        printf("child process.\n");
        sleep(30);
        printf("child process over.\n");
    }else{
        printf("father process,sleep before.\n");
        sleep(3);
        printf("father process,sleep after(wait before).\n");
        pid_t wait_ret=wait(NULL);
        printf("father process,wait after,wait_re=%d.\n",wait_ret);
    }
    return 0;
}


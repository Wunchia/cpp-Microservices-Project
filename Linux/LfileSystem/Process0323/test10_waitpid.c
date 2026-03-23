#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    pid_t fork_ret=fork();
    if(fork_ret==0){
        printf("child process begin.\n");
        sleep(20);
        printf("child process over.\n");
    }else{
        printf("father process begin.\n");
        pid_t wait_pid_ret=waitpid(fork_ret,NULL,WNOHANG);
        printf("father process waitpid over. ret=%d\n",wait_pid_ret);
    }
    return 0;
}


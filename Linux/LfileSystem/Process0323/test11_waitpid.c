#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    pid_t fork_ret=fork();
    if(fork_ret==0){
        printf("child process begin.\n");
        sleep(30);
        printf("child process over.\n");
    }else{
        pid_t wait_pid_ret=0;
        printf("father process begin.\n");
        bool wait_success=false;
        for(int i=0;i<60;i++){
            pid_t wait_pid_ret=waitpid(fork_ret,NULL,WNOHANG);
            if(wait_pid_ret>0){
                wait_success=true;
                break;
            }
            sleep(1);
        }
        if(wait_success){
            //后续操作
        }else{
            //retry();
        }
        printf("father process waitpid over.ret=%d\n",wait_pid_ret);
    }
    return 0;
}


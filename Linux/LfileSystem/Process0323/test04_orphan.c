#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    pid_t ret=fork();
    if(ret==0){
        printf("child process.\n");
        while(1){
            printf("child process running.\n");
            sleep(1);
        }
    }else{
        printf("father process.\n");
        sleep(5);
        printf("father process over.\n");
    }
    return 0;
}


#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    if(fork()==0){
        printf("child process,begin.\n");
        setsid();
        while(1){
            printf("child process running.\n");
            sleep(1);
        }
    }else{
        printf("father process,begin.\n");
        sleep(60);
        printf("father process over.\n");
    }
    return 0;
}


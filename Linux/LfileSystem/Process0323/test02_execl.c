#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    pid_t ret=fork();
    if(ret==0){
        printf("child process.\n");
        execl("./test02_cal","./test02_cal","8","7",(char*)NULL);
    }else{
        printf("father process.\n");
        sleep(20);
        printf("father over.\n");
    }
    return 0;
}


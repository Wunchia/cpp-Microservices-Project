#include <my_header.h>
void func(int num){
    printf("num : %d\n",num);
}
/*Usage: */

int main(int argc,char *argv[])
{
    pid_t pid=fork();
    if(0==pid){
        signal(2,func);
        while(1){
            sleep(1);
            printf("while\n");
        }
    }else{
        sleep(10);
        kill(pid,2);
    }
    return 0;
}


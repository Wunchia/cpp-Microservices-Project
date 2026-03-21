#include <my_header.h>
int global_num=11;
/*Usage: */
int main(int argc,char *argv[])
{
    int num=10;
    pid_t ret=fork();

    if(ret==0){
        printf("in child process.global_num=%d,num=%d\n",global_num,num);
    }else{
        global_num=22;
        num=20;
        printf("in father process.global_num=%d,num=%d\n",global_num,num);
    }
    return 0;
}


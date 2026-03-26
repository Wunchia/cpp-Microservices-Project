#include <my_header.h>
void func(int num){
    printf("num:%d\n",num);
}

/*Usage: */
int main(int argc,char *argv[])
{
    struct sigaction act,oldact;
    memset(&act,0,sizeof(act));
    act.sa_handler=func;
    act.sa_flags=SA_RESTART;
    sigaction(2,&act,&oldact);

    char buf[100]={0};
    int ret=read(STDIN_FILENO,buf,sizeof(buf));
    printf("read over\n");
    printf("%s\n",buf);
    if(strcmp(buf,"\n")==0){
        printf("ret=%d\n",ret);
    }
    return 0;
}


#include <my_header.h>

void func(int num){
    printf("func num:%d\n",num);
    exit(0);
}

/*Usage: */
int main(int argc,char *argv[])
{
    signal(10,func);

    int pipe_read=open("1.pipe",O_RDONLY);
    int pipe_write=open("2.pipe",O_WRONLY);

    int pid_b=getpid();
    int pid_a;

    write(pipe_write,&pid_b,sizeof(int));
    read(pipe_read,&pid_a,sizeof(int));

    fd_set set;
    FD_ZERO(&set);

    struct timeval tv;
    tv.tv_sec=10;
    tv.tv_usec=0;

    while(1){
        FD_SET(STDIN_FILENO,&set);
        FD_SET(pipe_read,&set);

        select(10,&set,NULL,NULL,&tv);

        if(FD_ISSET(STDIN_FILENO,&set)){
            char buf[10]={0};
            int res=read(STDIN_FILENO,buf,sizeof(buf));

            if(2==res&&1==atoi(buf)){
                kill(pid_a,10);
                kill(pid_b,10);
                return 0;
            }
            write(pipe_write,buf,sizeof(buf));
        }
        if(FD_ISSET(pipe_read,&set)){
            char buf[60]={0};
            int res=read(pipe_read,buf,sizeof(buf));
            if(0==res){
                printf("connecting pipe has been closed\n");
                break;
            }
            printf("A:%s\n",buf);
            tv.tv_sec=10;
            tv.tv_usec=0;
        }else{
            if(0==tv.tv_sec){
                printf("timeover disconnected\n");
                break;
            }
        }
    }

    close(pipe_read);
    close(pipe_write);
    return 0;
}


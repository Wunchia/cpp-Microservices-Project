#include <my_header.h>

void func(int num){
    printf("func num : %d\n",num);
    exit(0);
}

/*Usage: */
int main(int argc,char *argv[])
{
    //注册信号
    signal(10,func);

    //打开读写管道 a 1写 2读
    int pipe_write=open("1.pipe",O_WRONLY);
    int pipe_read=open("2.pipe",O_RDONLY);

    //pid_a 存自己的pid  定义pid_b准备存对方的pid
    int pid_a=getpid();
    int pid_b;

    //握手过程 接收userb的pid，再给对方传自己的pid
    read(pipe_read,&pid_b,sizeof(int));
    write(pipe_write,&pid_a,sizeof(int));

    fd_set set;
    FD_ZERO(&set);

    while(1){
        //IO多路复用同时监听标准输入和读端管道
        FD_SET(STDIN_FILENO,&set);
        FD_SET(pipe_read,&set);
        select(10,&set,NULL,NULL,NULL);

        //如果读到标准输入
        if(FD_ISSET(STDIN_FILENO,&set)){
            char buf[60]={0};
            int res=read(STDIN_FILENO,buf,sizeof(buf));

            //如果收到1 给所有进程发送10号信号
            if(2==res&&1==atoi(buf)){
                kill(pid_b,10);
                kill(pid_a,10);
                return 0;
            }
            //收到其他内容则向写端管道写
            write(pipe_write,buf,sizeof(buf));
        }

        //如果读到读端管道
        if(FD_ISSET(pipe_read,&set)){
            char buf[60]={0};
            int res=read(pipe_read,buf,sizeof(buf));
            if(0==res){
                printf("connecting pipe has been closed\n");
                break;
            }
            printf("B:%s\n",buf);
        }
    }

    close(pipe_read);
    close(pipe_write);

    return 0;
}


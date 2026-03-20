#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    //使用select 需要调用系统提供的宏
    fd_set readset;//定义一个用于描述 文件描述符集合的数据结构
                   //本质是一个位图 每一位表示该位对应的文件描述符是否被关注
                   //大小一般为1024 由FD_SETSIZE宏定义
    FD_ZERO(&readset);//初始化readset 所有位均置为0
    FD_SET(STDIN_FILENO,&readset);//将文件描述符0 放入fd_set

    //int select(int nfds, //要监听的最大文件描述符+1
    //fd_set *readfds, fd_set *writefds, fd_set *exceptfds,//分别指向读写异常
    //struct timeval *timeout);//设置超时时间
    int ret=select(10,&readset,NULL,NULL,NULL);//这里超时时间为NULL，会一直阻塞等待stdin输入
    //select的入参没有被const修饰，说明会修改
    //select结束之后，在fd_set中的文件描述符就是可用的文件描述符
    //同理每次select后，再次select前都需要重新初始化fd_set
    printf("ret=%d\n",ret);

    //FD_ISSET(int fd,fd_set* set);
    //检查就绪：判断 fd 是否在 set 中且已就绪（有事件发生）
    //就绪返回非 0，否则返回 0。
    
    //select()	>0：所有就绪 fd 的总数量；0：超时；-1：调用失败。
    //FD_ISSET()  非 0：指定 fd 就绪；0：指定 fd 未就绪。
    //          （仅做「是 / 否」判断，无数量意义
    //
    //          FD_ISSET()单次只能判断一个fd是否就绪
    if(FD_ISSET(STDIN_FILENO,&readset)){
        char buf[100]={0};
        read(STDIN_FILENO,buf,sizeof(buf));
        printf("read from stdin:%s\n",buf);
    }
    return 0;
}


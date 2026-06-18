// TCP编程：
// a.Daytime服务器（短连接）
// b.Echo服务器（长连接）
// c.ChatRoom服务器（长连接 且 连接之间有交互）

//Echo服务器
// 会把客户端发过来的字母转换成大写，然后再返回给客户端

#include "common.h"
#include <arpa/inet.h>
#include <atomic>
#include <cstdio>
#include <iostream>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>
using namespace std;

static const int BACKLOG=128;
static const int MAXEVENTS=1024;

int tcp_listen(uint16_t port)
{
    //1.创建主动套接字
    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd==-1)
    {
        perror("socket()");
        exit(-1);
    }
    //2.设置地址复用
    int opt=1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    //3.绑定套接字地址
    struct sockaddr_in addr;
    bzero(&addr,sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_port=htons(port);
    int err=bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
    if(err)
    {
        perror("bind()");
        exit(-1);
    }
    //4.将主动套接字转变为被动套接字
    // 主动套接字：接收和发送数据（接收缓冲区、发送缓冲区）
    // 被动套接字：等待连接的（半链接队列、已连接队列）
    err=listen(sockfd,BACKLOG);
    if(err)
    {
        perror("listen()");
        exit(-1);
    }
    cout<<"Server is listening..."<<endl;
    return sockfd;
}

int main(int argc,char *argv[])
{
    //1.绑定通配符地址 监听8888端口
    int listenfd=tcp_listen(8888);
    //2.创建epoll实例（红黑树、双向链表）
    int epfd=epoll_create(1);
    if(epfd==-1){
        perror("epoll_create()");
        exit(-1);
    }
    //3.将listenfd添加到epoll实例中（监听）
    struct epoll_event evt;
    evt.data.fd=listenfd;
    evt.events=EPOLLIN;
    int err=epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &evt);
    if(err)
    {
        perror("Add listenfd to epoll instance");
        exit(-1);
    }

    //4.事件循环
    for(;;){
        //等待事件发生
        struct epoll_event events[MAXEVENTS];//存放就绪事件
        int nready=epoll_wait(epfd, events, MAXEVENTS, -1);
        if(nready<0){
            perror("epoll_wait()");
            break;
        }

        // 处理事件
        for(int i=0;i<nready;++i)
        {
            if((events[i].events&EPOLLIN)==0){//和EPOLLIN按位与，不为零说明是读事件（这里用来过滤非读事件）
                continue;
            }
            //a.新连接到达（事件1）
            if(events[i].data.fd==listenfd){
                struct sockaddr_in cliaddr;//用于接收客户端地址
                socklen_t length=sizeof(cliaddr);
                int connfd=accept(listenfd,(struct sockaddr*)&cliaddr,&length);
                if(connfd==-1){
                    perror("accept()");
                    continue;
                }
                evt.events=EPOLLIN;
                evt.data.fd=connfd;
                epoll_ctl(epfd,EPOLL_CTL_ADD,connfd,&evt);
                //打印日志信息
                char ipstr[INET_ADDRSTRLEN];
                inet_ntop(AF_INET, &cliaddr.sin_addr, ipstr, INET_ADDRSTRLEN);
                uint16_t port=ntohs(cliaddr.sin_port);
                printf("新连接建立，客户端地址为 %s:%hu\n", ipstr, port);
            }else{
                char buf[4096];
                int connfd=events[i].data.fd;
                int nbytes=recv(connfd,buf,sizeof(buf),0);
                if(nbytes<0){
                    perror("read()");
                    epoll_ctl(epfd, EPOLL_CTL_DEL, connfd, NULL);
                    close(connfd);
                }else if(nbytes==0){
            //b.客户端断开连接（事件2）
                    epoll_ctl(epfd, EPOLL_CTL_DEL, connfd, NULL);
                    close(connfd);
                    printf("客户端断开连接，关闭文件描述符%d\n",connfd);
                }else{
            //c.客户端有消息到达(事件3)
                    for(int j=0;j<nbytes;++j){
                        buf[j]=toupper(buf[j]);
                    }
                    send(connfd,buf,nbytes,0);
            //d.消息发送完毕（事件3.5，只能算半个事件）
                    printf("回显数据：%.*s\n",nbytes,buf);
                }
            }
        }
    }

    return 0;
}

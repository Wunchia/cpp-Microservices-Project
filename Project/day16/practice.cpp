#include <cstdio>
#include <iostream>
#include <netinet/in.h>
#include <strings.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include "common.h"

using namespace std;

static const int BACKLOG=128;
static const int MAXEVENTS=1024;

int tcp_listen(uint16_t port){
    //socket小连招  socket-->setsockopt-->bind-->listen
    // 创建套接字
    int sockfd=socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd==-1){
        perror("socket");
        exit(-1);
    }

    // 设置套接字选项，允许地址重用
    int opt=1;
    setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

    // 绑定套接字地址
    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_port=htons(port);
    if(bind(sockfd, (struct sockaddr *)&addr, sizeof(addr))){
        perror("bind");
        exit(-1);
    }

    // 监听套接字
    // BACKLOG是已连接队列的大小
    if(listen(sockfd, BACKLOG)){
        perror("listen");
        exit(-1);
    }

    cout<<"Server listening on port: "<<port<<endl;

    return sockfd;
}

int main(int argc,char *argv[])
{
    //绑定通配符地址（被动套接字）
    int listenfd = tcp_listen(8848);//0 标准输入 1 标准输出 2 标准错误 所以占用fd=3

    //创建epoll实例
    int epfd = epoll_create(1);//占用fd=4
    if(epfd==-1){
        perror("epoll_create");
        exit(-1);
    }

    //将listenfd添加到epoll实例中（这里开始监听）
    struct epoll_event ev;//有data和event两个成员
    ev.data.fd = listenfd;//这是一个union，指针或fd指向用户数据变量（这里用fd）
    ev.events = EPOLLIN;//这是一个enum枚举事件类型
    if(epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev)==-1){
        perror("epoll_ctl");
        exit(-1);
    }
    cout<<"listenfd: "<<listenfd<<endl;

    //事件循环（处理三个半事件）
    for(;;){
        struct epoll_event events[MAXEVENTS];
        int nready=epoll_wait(epfd,events,MAXEVENTS,-1);
        if(nready==-1){
            perror("epoll_wait");
            exit(-1);
        }
        //epoll_wait被唤醒 事件到达
        for(int i=0;i<nready;++i){
            //和EPOLLIN按位与，不为零说明是读事件（这里用来过滤非读事件）
            if((events[i].events&EPOLLIN)==0){
                continue;
            }

            // 有新连接到达（事件一）
            if(events[i].data.fd==listenfd){
                struct sockaddr_in cliaddr;
                socklen_t length=sizeof(cliaddr);
                //从已连接队列中取出
                int connfd=accept(listenfd,(struct sockaddr*)&cliaddr,&length);
                if(connfd==-1){
                    perror("accept");
                    continue;
                }
                //加入epoll
                ev.events=EPOLLIN;
                ev.data.fd=connfd;
                if(epoll_ctl(epfd,EPOLL_CTL_ADD,connfd,&ev)==-1){
                    perror("epoll_ctl");
                    continue;
                }
                //打印日志信息
                char ipstr[INET_ADDRSTRLEN];
                inet_ntop(AF_INET, &cliaddr.sin_addr, ipstr, INET_ADDRSTRLEN);
                uint16_t port=ntohs(cliaddr.sin_port);
                printf("new connection established，client addr: %s:%hu\n", ipstr, port);
            }else{
                int connfd=events[i].data.fd;
                char buf[4096];
                int nbytes=recv(connfd,buf,sizeof(buf),0);
                if(nbytes<0){
                    // 接收数据出错
                    perror("recv");
                    epoll_ctl(epfd, EPOLL_CTL_DEL, connfd, NULL);
                    close(connfd);
                }else if(nbytes==0){
                    // 客户端断开连接（事件二）
                    epoll_ctl(epfd, EPOLL_CTL_DEL, connfd, NULL);
                    close(connfd);
                    printf("client disconnected,close fd:%d\n",connfd);
                }else{
                    // 客户端有消息到达（事件三）
                    // （Echo 转大写）
                    for(int j=0;j<nbytes;++j){
                        buf[j]=toupper(buf[j]);
                    }
                    send(connfd,buf,nbytes,0);
                    // 消息发送完毕（事件3.5）
                    printf("send data:%.*s\n",nbytes,buf);
                }
            }
        }
    }
}

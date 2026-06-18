#include <arpa/inet.h>
#include <cctype>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <sys/epoll.h>

using namespace std;

static const int BACKLOG=128;
static const int MAXEVENTS=1024;

int tcp_listen(uint16_t port){
    //socket 小连招：socket-->setsockopt-->bind-->listen
    int sockfd=socket(AF_INET,SOCK_STREAM,0);

    int opt=1;
    setsockopt(sockfd, SOL_SOCKET,SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in addr{};
    addr.sin_family=AF_INET;
    addr.sin_port=htons(port);
    addr.sin_addr.s_addr=INADDR_ANY;
    if(bind(sockfd,(struct sockaddr*)&addr,sizeof(addr))<0){
        cerr<<"[ERROR]:bind()"<<endl;
        exit(-1);
    }

    listen(sockfd,BACKLOG);

    cout<<"Server is listening on port "+to_string(port)<<endl;
    return sockfd;
}

int main(int argc,char *argv[])
{
    int listenfd=tcp_listen(8848);

    int epfd=epoll_create(1);

    struct epoll_event evt;
    evt.events=EPOLLIN;
    evt.data.fd=listenfd;//这里是传给evt，后面取出来自己用
    epoll_ctl(epfd,EPOLL_CTL_ADD, listenfd, &evt);//这里传的listenfd是告诉内核

    //事件循环 处理三个半事件
    for(;;){
        struct epoll_event events[MAXEVENTS];
        int nready=epoll_wait(epfd, events,MAXEVENTS,-1);
        if(nready==-1){
            if(errno==EINTR){
                continue;//被信号打断时并不是真错 继续循环
            }
            cerr<<"[ERROR]:epoll_wait errno="<<errno<<" "<<strerror(errno)<<endl;
            exit(-1);
        }

        for(int i=0;i<nready;++i){
            if((events[i].events&EPOLLIN)==0){
                continue;//非读事件 跳过
            }

            // 事件一：有新连接到达
            if(events[i].data.fd==listenfd){
                //connfd 从 accept 来 然后 加入epoll
                struct sockaddr_in cliaddr;
                socklen_t cliaddr_len=sizeof(cliaddr);
                int connfd=accept(listenfd, (struct sockaddr*)&cliaddr, &cliaddr_len);

                //直接复用前面的epoll_event结构体
                evt.events=EPOLLIN;
                evt.data.fd=connfd;
                epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &evt);

                //通过cliaddr 取出accept的连接的信息 进行日志打印
                char ipstr[INET_ADDRSTRLEN];
                inet_ntop(AF_INET, &cliaddr.sin_addr, ipstr, INET_ADDRSTRLEN);
                uint16_t port=ntohs(cliaddr.sin_port);
                cout<<"new connection established，client addr --"<<ipstr<<" : "<<port<<endl;
            }else{
                //从已有连接里读数据出来
                // connfd 从 events[i].data.fd 来
                int connfd=events[i].data.fd;
                char buf[4096];
                int nbytes=recv(connfd,buf,sizeof(buf),0);
                if(nbytes<0){
                    cerr<<"recv error"<<endl;
                    epoll_ctl(epfd,EPOLL_CTL_DEL, connfd, NULL);
                    close(connfd);
                }else if(nbytes==0){
            // 事件二：客户端断开连接
                    epoll_ctl(epfd,EPOLL_CTL_DEL, connfd, NULL);
                    close(connfd);
                    cout<<"client: "<<connfd<<" is closed."<<endl;
                }else{
            // 事件三：客户端有消息到达
                    for(int j=0;j<nbytes;++j){
                        buf[j]=toupper(buf[j]);
                    }
            // 事件3.5：消息发送完毕（本机写入成功）
                    send(connfd,buf,nbytes,0);
                    // send只代表把数据从应用缓冲区拷贝到了内核TCP缓冲区
                    // 不代表对端应用层收到了数据 只能算半个事件
                    printf("send data: %.*s\n",nbytes,buf);
                }
            }
        }
    }
}

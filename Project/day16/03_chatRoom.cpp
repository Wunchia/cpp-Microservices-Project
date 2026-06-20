// chatroom_server 聊天室：多客户端长连接，消息广播
#include <arpa/inet.h>
#include <asm-generic/socket.h>
#include <cerrno>
#include <cstdint>
#include <cstring>
#include <netinet/in.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/epoll.h>
#include <sys/socket.h>

using namespace std;

static const int BACKLOG=128;
static const int MAXEVENTS=1024;
static const int MAXCLI=512;
static const int BUFSIZE=4096;

//保存每个客户端的fd和ip
int cli_fds[MAXCLI];
char cli_ips[MAXCLI][INET_ADDRSTRLEN];
int cli_count=0;

//广播消息给所有客户端（除了发送者）
void broadcast(int sender_fd,const char *msg,int len){
    char buf[BUFSIZE+64];
    // 找到发送者IP
    const char *sender_ip="unknown";
    for(int i=0;i<cli_count;++i){
        if(cli_fds[i]==sender_fd){
            sender_ip=cli_ips[i];
            break;
        }
    }

    //格式化消息：[ip] 内容
    int total=snprintf(buf,sizeof(buf),"[%s]%.*s",sender_ip,len,msg);

    for(int i=0;i<cli_count;++i){
        if(cli_fds[i]!=sender_fd){
            send(cli_fds[i],buf,total,0);
        }
    }
}

int tcp_listen(uint16_t port){
    int sockfd=socket(AF_INET,SOCK_STREAM,0);

    int opt=1;
    setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

    struct sockaddr_in addr{};
    addr.sin_family=AF_INET;
    addr.sin_port=htons(port);
    addr.sin_addr.s_addr=INADDR_ANY;
    if(bind(sockfd,(struct sockaddr*)&addr,sizeof(addr))<0){
        cerr<<"[ERROR]:bind()"<<endl;
        exit(-1);
    }

    listen(sockfd,BACKLOG);

    cout<<"Chatroom server listening on port "+to_string(port)<<endl;
    return sockfd;
}

int main(int argc,char *argv[])
{
    int listenfd=tcp_listen(8848);

    int epfd=epoll_create(1);

    struct epoll_event evt;
    evt.events=EPOLLIN;
    evt.data.fd=listenfd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &evt);

    //事件处理
    for(;;){
        struct epoll_event events[MAXEVENTS];
        int nready=epoll_wait(epfd,events,MAXEVENTS,-1);
        if(nready==-1){
            if(errno==EINTR){
                continue;
            }
            cerr<<"[ERROR]: epoll_wait error="<<errno<<" "<<strerror(errno)<<endl;
            exit(-1);
        }

        for(int i=0;i<nready;++i){
            if((events[i].events&EPOLLIN)==0){
                continue;
            }

            //新连接到达
            if(events[i].data.fd==listenfd){
                struct sockaddr_in cliaddr;
                socklen_t cliaddr_len=sizeof(cliaddr);
                int connfd=accept(listenfd, (struct sockaddr*)&cliaddr, &cliaddr_len);

                if(cli_count>=MAXCLI){
                    cerr<<"[WARN]:max clients reached,rejecting connection."<<endl;
                    close(connfd);
                    continue;
                }

                //加入epoll
                evt.events=EPOLLIN;
                evt.data.fd=connfd;
                epoll_ctl(epfd, EPOLL_CTL_ADD, connfd,&evt);

                //记录客户端信息
                cli_fds[cli_count]=connfd;
                inet_ntop(AF_INET,&cliaddr.sin_addr,cli_ips[cli_count],INET_ADDRSTRLEN);
                ++cli_count;

                //日志打印
                char ipstr[INET_ADDRSTRLEN];
                inet_ntop(AF_INET,&cliaddr.sin_addr,ipstr,INET_ADDRSTRLEN);
                uint16_t port=ntohs(cliaddr.sin_port);
                cout << "new connection established，client addr --" << ipstr << " : " << port
                                    << "  total clients: " << cli_count << endl;

                //广播加入通知
                char join_msg[128];
                int join_len=snprintf(join_msg,sizeof(join_msg),"joined the chatroom!");
                broadcast(connfd,join_msg,join_len);
            }else{
                //从已有连接里读数据出来
                int connfd=events[i].data.fd;
                char buf[BUFSIZE];
                int nbytes=recv(connfd,buf,sizeof(buf),0);
                if(nbytes<0){
                    cerr<<"recv error"<<endl;
                    epoll_ctl(epfd, EPOLL_CTL_DEL, connfd, NULL);
                    close(connfd);
                    // 从客户端列表中移除
                    for(int j=0;j<cli_count;++j){
                        if(cli_fds[j]==connfd){
                            cli_fds[j]=cli_fds[cli_count-1];
                            strcpy(cli_ips[j],cli_ips[cli_count-1]);
                            --cli_count;
                            break;
                        }
                    }
                }else if(nbytes==0){
                    epoll_ctl(epfd,EPOLL_CTL_DEL,connfd,NULL);
                    close(connfd);
                    cout<<"client: "<<connfd<<" is closed."<<endl;

                    //从客户端列表中移除
                    for(int j=0;j<cli_count;++j){
                        if(cli_fds[j]==connfd){
                            char leave_msg[128];
                            int leave_len=snprintf(leave_msg,sizeof(leave_msg),"left the chatroom.");
                            broadcast(connfd,leave_msg,leave_len);

                            cli_fds[j]=cli_fds[cli_count-1];
                            strcpy(cli_ips[j],cli_ips[cli_count-1]);
                            --cli_count;
                            break;
                        }
                    }
                }else{
                    // 事件三：客户端有消息到达 --> 广播给其他所有人
                    broadcast(connfd, buf, nbytes);
                }
            }
        }
    }
    close(listenfd);
    return 0;
}

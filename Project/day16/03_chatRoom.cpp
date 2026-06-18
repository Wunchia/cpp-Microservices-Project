// chatroom_server 聊天室：多客户端长连接，消息广播
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>

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
void broadcast(int epfd,int sender_fd,const char *msg,int len){
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

    }
}

int main(int argc,char *argv[])
{

    return 0;
}

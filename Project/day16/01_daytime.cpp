//daytime_server--短连接：发送后立即关闭
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

static const int BACKLOG=128;
static const int BUFSIZE=1024;

int main(int argc,char *argv[])
{
    //socket 小连招：socket-->setsockopt-->bind-->listen
    int listenfd=socket(AF_INET,SOCK_STREAM,0);
    if(listenfd<0){
        perror("socket");
        exit(-1);
    }

    int opt=1;
    setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

    struct sockaddr_in addr;
    bzero(&addr,sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_port=htons(1313);
    if(bind(listenfd,(struct sockaddr*)&addr,sizeof(addr))<0){
        perror("bind");
        exit(-1);
    }

    if(listen(listenfd,BACKLOG)<0){
        perror("listen");
        exit(-1);
    }
    printf("Daytime server listening on port 1313...\n");

    for(;;){
        //处理事件
        // 新连接到达：accept
        struct sockaddr_in cliaddr;
        socklen_t clilen=sizeof(cliaddr);
        int connfd=accept(listenfd,(struct sockaddr*)&cliaddr,&clilen);
        if(connfd<0){
            perror("accept()");
            continue;
        }

        char ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &cliaddr.sin_addr,ip,sizeof(ip));
        printf("client %s:%hu connected\n",ip,ntohs(cliaddr.sin_port));

        //获取当前时间并发送
        time_t now=time(NULL);
        char *timestr=ctime(&now);
        send(connfd,timestr,strlen(timestr),0);

        //短连接 发完就关闭
        close(connfd);
        printf("daytime sent, connection closing\n");
    }

    close(listenfd);
    return 0;
}

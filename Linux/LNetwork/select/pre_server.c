#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    char *sourceIP="192.168.171.128";
    char *sourcePort="12345";

    int socketFd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(socketFd,-1,"socket");

    //课件上的赋值写法 看看
    // struct in_addr inAddr;
    // inet_aton(sourceIP,&inAddr);
    // int sourcePortInt=atoi(sourcePort);
    // int sourcePortNet=htons(sourcePortInt);

    struct sockaddr_in socketAddr;
    memset(&socketAddr,0,sizeof(socketAddr));

    socketAddr.sin_family=AF_INET;
    socketAddr.sin_addr.s_addr=inet_addr(sourceIP);
    socketAddr.sin_port=htons(atoi(sourcePort));

    //绑定
    int res_bind=bind(socketFd,(struct sockaddr*)&socketAddr,sizeof(socketAddr));
    ERROR_CHECK(res_bind,-1,"res_bind");

    //监听
    int ret=listen(socketFd,10);
    ERROR_CHECK(ret,-1,"listen");

    //接收链接
    int connFd=accept(socketFd,NULL,NULL);
    ERROR_CHECK(connFd,-1,"accepte");

    //在数据传输过程中采用IO多路复用
    fd_set read_fd_set;
    while(1){
        FD_ZERO(&read_fd_set);
        FD_SET(connFd,&read_fd_set);
        FD_SET(STDIN_FILENO,&read_fd_set);
        select(connFd+1,&read_fd_set,NULL,NULL,NULL);

        if(FD_ISSET(connFd,&read_fd_set)){
            char buf[60]={0};
            int res_recv=recv(connFd,buf,sizeof(buf),0);
            ERROR_CHECK(res_recv,-1,"recv");
            if(0==res_recv){
                printf("客户端发送结束\n");
                break;
            }
            write(STDOUT_FILENO,buf,sizeof(buf));
        }

        if(FD_ISSET(STDIN_FILENO,&read_fd_set)){
            char buf[60]={0};
            int res_read=read(STDIN_FILENO,buf,sizeof(buf)-1);
            if(0==res_read){
                break;
            }
            int res_send=send(connFd,buf,sizeof(buf),0);
            ERROR_CHECK(res_send,-1,"send");
        }
    }

    //四次挥手
    close(connFd);
    close(socketFd);

    return 0;
}


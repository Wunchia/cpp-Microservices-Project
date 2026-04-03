#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    char *ip="192.168.171.128";
    char *port="12345";

    int client_fd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(client_fd,-1,"socker");

    //用sockaddr_in存放ip和端口号
    struct sockaddr_in addr;

    memset(&addr,0,sizeof(addr));

    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=inet_addr(ip);
    addr.sin_port=htons(atoi(port));

    //客户端发起三次握手
    int ret=connect(client_fd,(struct sockaddr*)&addr,sizeof(addr));
    ERROR_CHECK(ret,-1,"connect");

    //--------数据传输阶段-----------
    //发
    int cnt=send(client_fd,"test from client",16,0);
    printf("\n---send cnt:%d---\n",cnt);

    //收
    char buf[100]={0};
    cnt=recv(client_fd,buf,sizeof(buf),0);
    printf("-----\nrecv cnt=%d\n",cnt);
    printf("msg: %s\n-----\n",buf);
    printf("\n---send cnt:%d---\n",cnt);
    //-------数据传输阶段结束-------
    
    sleep(5);

    close(client_fd);//四次挥手

    return 0;
}


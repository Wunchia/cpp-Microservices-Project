#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    char*ip="192.168.171.128";
    char*port="12345";
    
    int client_fd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(client_fd,-1,"socket");

    struct sockaddr_in addr;
    memset(&addr,0,sizeof(addr));

    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=inet_addr(ip);
    addr.sin_port=htons(atoi(port));

    int ret=connect(client_fd,(struct sockaddr*)&addr,sizeof(addr));
    ERROR_CHECK(ret,-1,"connect");

    int cnt=send(client_fd,"client",7,0);
    printf("send cnt:%d\n",cnt);

    char buf[100]={0};
    cnt=recv(client_fd,buf,sizeof(buf),0);
    printf("recv cnt:%d\n",cnt);
    printf("client buf:%s\n",buf);

    sleep(10);

    close(client_fd);

    return 0;
}


#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    char *ip="192.168.171.128";
    char *port="12345";
    
    int fd=socket(AF_INET,SOCK_DGRAM,0);
    ERROR_CHECK(fd,-1,"socket");

    struct sockaddr_in addr,client_addr;
    memset(&addr,0,sizeof(addr));

    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=inet_addr(ip);
    addr.sin_port=htons(atoi(port));

    socklen_t len=sizeof(client_addr);

    int ret=bind(fd,(struct sockaddr*)&addr,sizeof(addr));
    ERROR_CHECK(ret,-1,"bind");

    char buf[50]={0};
    recvfrom(fd,buf,sizeof(buf),0,(struct sockaddr*)&client_addr,&len);
    printf("msg from client:%s\n",buf);

    sendto(fd,"hi",2,0,(struct sockaddr*)&client_addr,sizeof(client_addr));

    close(fd);
    return 0;
}


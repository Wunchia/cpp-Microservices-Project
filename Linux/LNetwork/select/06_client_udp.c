#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    char *ip="192.168.171.128";
    char *port="12345";

    int fd=socket(AF_INET,SOCK_DGRAM,0);
    ERROR_CHECK(fd,-1,"socket");

    struct sockaddr_in addr;
    memset(&addr,0,sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=inet_addr(ip);
    addr.sin_port=htons(atoi(port));

    sendto(fd,"hello",5,0,(struct sockaddr*)&addr,sizeof(addr));

    char buf[50]={0};
    recvfrom(fd,buf,sizeof(buf),0,NULL,NULL);
    printf("recv from server:%s\n",buf);

    close(fd);

    return 0;
}


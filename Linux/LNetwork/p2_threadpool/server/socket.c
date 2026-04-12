#include <my_header.h>
#include "socket.h"
void init_socket(int *listen_fd,char*ip,char*port){
    *listen_fd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(*listen_fd,-1,"socket");

    int opt=1;
    int ret=setsockopt(*listen_fd,SOL_SOCKET,SO_REUSEPORT,&opt,sizeof(opt));
    ERROR_CHECK(ret,-1,"setsockopt");

    struct sockaddr_in addr;
    memset(&addr,0,sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=inet_addr(ip);
    addr.sin_port=htons(atoi(port));

    ret=bind(*listen_fd,(struct sockaddr*)&addr,sizeof(addr));
    ERROR_CHECK(ret,-1,"bind");

    ret=listen(*listen_fd,100);
    ERROR_CHECK(ret,-1,"listen");

}
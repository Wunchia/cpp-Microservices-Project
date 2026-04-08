#include <my_header.h>
#include "socket.h"

void init_socket(int *listen_fd,char *ip,char *port){
    //创建socket_struct与listen_fd关联 用于监听端口
    *listen_fd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(*listen_fd,-1,"socket");

    //设置端口复用
    int opt=1;
    int ret=setsockopt(*listen_fd,SOL_SOCKET,SO_REUSEPORT,&opt,sizeof(opt));
    ERROR_CHECK(ret,-1,"setsockopt");

    //绑定服务器的ip、端口号和socket_struct
    struct sockaddr_in addr;
    memset(&addr,0,sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=inet_addr(ip);
    addr.sin_port=htons(atoi(port));

    ret=bind(*listen_fd,(struct sockaddr*)&addr,sizeof(addr));
    ERROR_CHECK(ret,-1,"bind");

    //开始监听端口 维护半链接队列和全链接队列
    ret=listen(*listen_fd,100);
    ERROR_CHECK(ret,-1,"listen");
}

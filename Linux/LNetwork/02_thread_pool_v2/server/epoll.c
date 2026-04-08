#include <my_header.h>
#include "epoll.h"

//将fd放到红黑树上监听
void add_epoll_fd(int epfd,int fd){
    struct epoll_event evt;
    evt.events=EPOLLIN;//读事件 监听的事件类型
    evt.data.fd=fd;//存入需要监听的文件描述符

    int ret=epoll_ctl(epfd,EPOLL_CTL_ADD,fd,&evt);
    ERROR_CHECK(ret,-1,"epoll_ctl add");
}

//将fd从红黑树上取消监听
void del_epoll_fd(int epfd,int fd){
    struct epoll_event evt;
    evt.events=EPOLLIN;//监听的事件类型为 读事件
    evt.data.fd=fd;//存入监听的文件描述符

    int ret=epoll_ctl(epfd,EPOLL_CTL_DEL,fd,&evt);
    ERROR_CHECK(ret,-1,"epoll_ctl del");
}
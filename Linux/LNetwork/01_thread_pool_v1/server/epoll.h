#ifndef __EPOLL_H__
#define __EPOLL_H__

//主要用于实现对 epoll_ctl() 操作的封装

//将fd放到红黑树上监听
void add_epoll_fd(int epfd,int fd);

//将fd从红黑树上取消监听
void del_epoll_fd(int epfd,int fd);

#endif

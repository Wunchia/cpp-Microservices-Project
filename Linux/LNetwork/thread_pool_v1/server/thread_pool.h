#ifndef __THREADPOOL__
#define __THREADPOOL__

#include <my_header.h>
#include "queue.h"

typedef struct thread_pool{
    //所有子线程id
    pthread_t *thread_id_arr;
    //子线程的数量
    int thread_num;
    //任务队列
    queue_t queue;
    //锁
    pthread_mutex_t pool_lock;
    //条件变量
    pthread_cond_t cond;
}thread_pool_t;

//根据指定数量创建线程池
int init_thread_pool(thread_pool_t *pool,int num);

//定义线程的入口函数
void *threadMain(void *p);

//初始化链接
int initTcpSocket(int *socketfd,char *ip,char *port);

//添加epoll监听
int epoll_addfd(int epollfd,int filefd);

//传送文件
int sendFile(int net_fd);

#endif

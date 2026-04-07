#include <my_header.h>
#include "thread_pool.h"

void *thread_func(void*arg){
    thread_pool_t *pool =(thread_pool_t *)arg;

    //写线程需要执行的逻辑
    while(1){
        //从队列中拿数据，因为队列是共享资源，就要上锁
        pthread_mutex_lock(&pool->pool_lock);

        //如果队列是空的，工作线程只能睡眠
        //只有队列不空的时候，才能从队列中取数据
        while(pool->queue.size==0){
            pthread_cond_wait(&pool->cond,&pool->pool_lock);
        }
        //只有队列不空的时候，才能从队列中取数据
        //获取文件描述符
        int fd=pool->queue.head->fd;

        //出队
        deQueue(&pool->queue);

        //解锁
        pthread_mutex_unlock(&pool->pool_lock);

        //利用文件描述符将数据发给客户端
        send_file(fd);

        close(fd);
    }

    return NULL;
}
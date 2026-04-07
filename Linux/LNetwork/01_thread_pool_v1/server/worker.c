#include <my_header.h>
#include "worker.h"
#include "thread_pool.h"
#include "send_file.h"

void *thread_func(void *arg){
    //先强制类型转换 将pool从void*转回thread_pool_t*类型
    thread_pool_t *pool=(thread_pool_t*)arg;

    //线程需要执行的逻辑 从就绪的fd中取数据 然后向客户端发送
    while(1){
        //因为队列是共享资源 所以需要先上锁 再操作
        pthread_mutex_lock(&pool->lock);

        //无就绪fd时wait 循环用while防止虚假唤醒
        while(0==pool->queue.size){
            pthread_cond_wait(&pool->cond,&pool->lock);
        }

        //队列不为空时 从队头开始取
        // int fd=pool->queue.head->fd;
        int fd=0;
        deQueue(&pool->queue,&fd);

        //操作完成后解锁
        pthread_mutex_unlock(&pool->lock);

        send_file(fd);

        close(fd);
    }

    return NULL;
}

#include <my_header.h>
#include "worker.h"
#include "thread_pool.h"
#include "send_file.h"

void cleanup_lock(void*p){
    pthread_mutex_t *lock=(pthread_mutex_t*)p;
    pthread_mutex_unlock(lock);
}

void *thread_func(void *arg){
    thread_pool_t *pool=(thread_pool_t*)arg;

    while(1){
        int fd=0;
        pthread_mutex_lock(&pool->lock);

        pthread_cleanup_push(cleanup_lock,&pool->lock);

        while(0==pool->queue.size){
            //这个函数里有取消点 
            //当等待时遇到主线程的 pthread_cancel 则退出
            //退出时走cleanup_pop弹出的线程清理函数 释放锁
            pthread_cond_wait(&pool->cond,&pool->lock);
        }

        deQueue(&pool->queue,&fd);

        pthread_cleanup_pop(1);//在线程清理函数中 解开互斥锁

        send_file(fd);

        close(fd);
    }

    return NULL;

}
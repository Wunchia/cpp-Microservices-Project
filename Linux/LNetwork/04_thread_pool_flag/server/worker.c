#include <my_header.h>
#include "worker.h"
#include "thread_pool.h"
#include "send_file.h"


void *thread_func(void *arg){
    thread_pool_t *pool=(thread_pool_t*)arg;

    while(1){
        int fd=0;
        pthread_mutex_lock(&pool->lock);

        while(0==pool->queue.size&&0==pool->exitFlag){
            pthread_cond_wait(&pool->cond,&pool->lock);
        }

        if(1==pool->exitFlag){
            pthread_mutex_unlock(&pool->lock);
            pthread_exit((void*)NULL);
        }

        deQueue(&pool->queue,&fd);

        send_file(fd);

        close(fd);
    }

    return NULL;

}
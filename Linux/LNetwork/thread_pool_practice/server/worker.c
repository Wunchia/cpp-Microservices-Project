#include <my_header.h>
#include "worker.h"
#include "thread_pool.h"
#include "send_file.h"

void*thread_func(void*arg){
    thread_pool_t*pool=(thread_pool_t*)arg;

    //看队列里有无就绪fd 有则取出传输
    while(1){
        int fd=0;
        pthread_mutex_lock(&pool->lock);

        while(0==pool->queue.size&&0==pool->exitFlag){
            pthread_cond_wait(&pool->cond,&pool->lock);
        }

        //收到信号时，处理结束线程的逻辑
        if(1==pool->exitFlag&&0==pool->queue.size){
            pthread_mutex_unlock(&pool->lock);
            pthread_exit((void*)NULL);
        }

        //收到fd就绪时，处理文件传输的逻辑
        deQueue(&pool->queue,&fd);

        pthread_mutex_unlock(&pool->lock);

        send_file(fd);

        close(fd);
    }

    return NULL;
}
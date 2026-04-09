#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include "queue.h"
#include <my_header.h>

typedef struct thread_pool{
    int thread_num;//线程池中线程数量
    pthread_t *thread_id_arr;//维护线程id的数组
    queue_t queue;//就绪事件队列
    pthread_mutex_t lock;//互斥锁
    pthread_cond_t cond;//条件变量
    int exitFlag;//退出的标志位
}thread_pool_t;

void init_thread_pool(thread_pool_t *pool,int num);

#endif

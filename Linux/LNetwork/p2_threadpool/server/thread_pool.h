#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include <my_header.h>
#include "queue.h"

typedef struct thread_pool{
    int thread_num;
    int exitFlag;
    pthread_t* thread_id_arr;
    queue_t *queue;
    pthread_mutex_t lock;
    pthread_cond_t cond;  
}thread_pool_t;

void init_thread_pool(thread_pool_t*pool,int num);

#endif
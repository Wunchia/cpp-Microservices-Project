#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include "queue.h"
#include <my_header.h>

typedef struct thread_pool{
    
    //线程池中线程的数目
    int thread_num;

    //每个线程的id 用一个数组保存
    pthread_t *thread_id_arr;

    //就绪的fd 放入队列（队列中节点的data域是fd）
    queue_t queue;

    //互斥锁
    pthread_mutex_t lock;

    //条件变量
    pthread_cond_t cond;

}thread_pool_t;

//拉起一个线程池 num为池中线程数量
void init_thread_pool(thread_pool_t *pool,int num);

#endif
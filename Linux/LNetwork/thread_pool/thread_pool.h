#ifndef __THREADPOOL__
#define __THREADPOOL__

#include <my_header.h>
#include "queue.h"

typedef struct pool_s{
    //所有子线程id
    pthread_t *threadIds;
    //子线程的数量
    int threadNum;
    //任务队列
    queue_t queue;
    //锁
    pthread_mutex_t pool_lock;
    //条件变量
    pthread_cond_t cond;
}pool_t;

//根据指定数量创建线程池
int initPool(pool_t *pPool,int num);



#endif

#include <my_header.h>
#include "thread_pool.h"
#include "worker.h"
//拉起一个线程池 num为池中线程数量
void init_thread_pool(thread_pool_t *pool,int num){
    
    //为线程池中的线程数量赋值
    pool->thread_num=num;

    //互斥锁的初始化
    pthread_mutex_init(&pool->lock,NULL);

    //条件变量的初始化
    pthread_cond_init(&pool->cond,NULL);

    //队列初始化
    memset(&pool->queue,0,sizeof(queue_t));

    //给线程id数组分配空间
    pool->thread_id_arr=(pthread_t*)malloc(num*sizeof(pthread_t));
    //创建线程  因为thread_func需要参数
    //(会用到互斥锁 条件变量等) 所以一定要传入pool
    for(int idx=0;idx<num;++idx){
        int ret=pthread_create(&pool->thread_id_arr[idx],NULL,thread_func,(void*)pool);
        ERROR_CHECK(ret,-1,"pthread_create");
    }
}
#include "thread_pool.h"
#include "worker.h"

int init_thread_pool(thread_pool_t *pool,int num){
    //初始化子线程的数目
    pool->thread_num=num;

    //互斥锁的初始化
    pthread_mutex_init(&pool->pool_lock,NULL);

    //条件变量的初始化
    pthread_cond_init(&pool->cond,NULL);

    //初始化队列
    memset(&pool->queue,0,sizeof(queue_t));

    //为线程id所对应的指针分配空间
    pool->thread_id_arr=(pthread_t*)malloc(num*sizeof(pthread_t));

    for(int idx=0;idx<num;++idx){
        //需要将pool变量传入到thread_func(线程入口函数)中
        //因为会用到互斥锁、条件变量等
        int ret=pthread_create(&pool->thread_id_arr[idx],NULL,thread_func,(void*)pool);
        ERROR_CHECK(ret,-1,"pthread_create");
    }
}
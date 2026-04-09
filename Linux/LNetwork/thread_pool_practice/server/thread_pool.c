#include "thread_pool.h"
#include "worker.h"
void init_thread_pool(thread_pool_t* pool,int thread_num){
    pool->exitFlag=0;
    pool->thread_num=thread_num;
    pthread_mutex_init(&pool->lock,NULL);
    pthread_cond_init(&pool->cond,NULL);
    memset(&pool->queue,0,sizeof(queue_t));
    
    pool->thread_id_arr=(pthread_t*)malloc(thread_num*sizeof(pthread_t));
    for(int idx=0;idx<thread_num;++idx){
        int ret=create(&pool->thread_id_arr[idx],NULL,thread_func,(void*)pool);
        ERROR_CHECK(ret,-1,"create_pthread");
    }
}
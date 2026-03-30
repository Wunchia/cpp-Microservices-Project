#include <my_header.h>
pthread_mutex_t lock;
pthread_cond_t cond;

void *thread_func(void*arg){
    sleep(1);
    int ret=pthread_mutex_lock(&lock);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_lock");

    printf("I am sonA\n");
    // sleep(10);
    pthread_cond_signal(&cond);

    ret=pthread_mutex_unlock(&lock);
    THREAD_ERROR_CHECK(ret,"son pthread_mutex_unlock");

    pthread_exit((void*)NULL);
}

/*Usage: */
int main(int argc,char *argv[])
{
    //初始化锁
    int ret=pthread_mutex_init(&lock,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_init");
    //初始化条件变量
    ret=pthread_cond_init(&cond,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_cond_init");
    //创建子线程
    pthread_t thread_id;
    ret=pthread_create(&thread_id,NULL,thread_func,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_createA");

    //上锁    
    ret=pthread_mutex_lock(&lock);
    THREAD_ERROR_CHECK(ret,"main pthread_mutex_lock");
    
    printf("begin wait\n");
    struct timeval now;
    struct timespec tm;
    gettimeofday(&now,NULL);
    tm.tv_sec=now.tv_sec+10;
    tm.tv_nsec=0;
    ret=pthread_cond_timedwait(&cond,&lock,&tm);
    THREAD_ERROR_CHECK(ret,"main pthread_cond_timedwait");
   if(0==ret){ 
        printf("I am main condition ok\n");
    }
    //解锁
    ret=pthread_mutex_unlock(&lock);
    THREAD_ERROR_CHECK(ret,"main pthread_mutex_unlock");
    
    ret=pthread_join(thread_id,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_joinB");
    //回收锁的资源
    ret=pthread_mutex_destroy(&lock);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_destroy");
    //销毁条件变量
    ret=pthread_cond_destroy(&cond);
    THREAD_ERROR_CHECK(ret,"pthread_cond_destroy");

    return 0;
}


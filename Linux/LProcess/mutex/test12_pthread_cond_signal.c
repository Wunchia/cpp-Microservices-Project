#include <my_header.h>
pthread_mutex_t lock;
pthread_cond_t cond;

void *thread_func(void*arg){
    sleep(1);
    int ret=pthread_mutex_lock(&lock);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_lock");

    printf("I am son\n");

    ret=pthread_cond_signal(&cond);
    THREAD_ERROR_CHECK(ret,"pthread_cond_signal");
    printf("son signaled\n");
    sleep(10);//子线程唤醒主线程后，主线程也要重新竞争lock
    //等到子线程unlock后 主线程拿到锁才能从pthread_cond_wait返回
    ret=pthread_mutex_unlock(&lock);
    THREAD_ERROR_CHECK(ret,"son pthread_mutex_unlock");

    pthread_exit(NULL);
}

/*Usage: */
int main(int argc,char *argv[])
{
    int ret=pthread_mutex_init(&lock,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_init");

    ret=pthread_cond_init(&cond,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_cond_init");

    pthread_t thread_id;
    ret=pthread_create(&thread_id,NULL,thread_func,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_create");

    ret=pthread_mutex_lock(&lock);
    THREAD_ERROR_CHECK(ret,"main pthread_mutex_lock");
    
    printf("begin wait\n");
    //没有满足条件 wait会解锁然后等待条件满足（原子操作）
    //条件满足后收到signal再唤醒，重新竞争lock
    ret=pthread_cond_wait(&cond,&lock);
    THREAD_ERROR_CHECK(ret,"pthread_cond_wait");

    printf("I am main condition ok\n");

    ret=pthread_mutex_unlock(&lock);
    THREAD_ERROR_CHECK(ret,"main pthread_mutex_unlock");

    ret=pthread_mutex_destroy(&lock);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_destroy");

    ret=pthread_cond_destroy(&cond);
    THREAD_ERROR_CHECK(ret,"pthread_cond_destroy");

    return 0;
}


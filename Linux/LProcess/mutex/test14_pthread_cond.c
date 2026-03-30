#include <my_header.h>
pthread_mutex_t lock;
pthread_cond_t cond;

void *thread_funcA(void*arg){
    sleep(1);
    int ret=pthread_mutex_lock(&lock);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_lockA");

    printf("sonA wait begin\n");
    ret=pthread_cond_wait(&cond,&lock);
    THREAD_ERROR_CHECK(ret,"pthread_cond_waitA");
    printf("sonA wait end\n");

    printf("I am sonA\n");

    ret=pthread_mutex_unlock(&lock);
    THREAD_ERROR_CHECK(ret,"son pthread_mutex_unlock");

    pthread_exit((void*)NULL);
}

void *thread_funcB(void*arg){
    sleep(1);
    int ret=pthread_mutex_lock(&lock);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_lockB");

    printf("sonB wait begin\n");
    ret=pthread_cond_wait(&cond,&lock);
    THREAD_ERROR_CHECK(ret,"pthread_cond_waitB");
    printf("sonB wait end\n");

    printf("I am sonB\n");

    ret=pthread_mutex_unlock(&lock);
    THREAD_ERROR_CHECK(ret,"son pthread_mutex_unlockB");

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
    pthread_t thread_idA,thread_idB;
    ret=pthread_create(&thread_idA,NULL,thread_funcA,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_createA");

    ret=pthread_create(&thread_idB,NULL,thread_funcB,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_createB");
    //上锁    
    // ret=pthread_mutex_lock(&lock);
    // THREAD_ERROR_CHECK(ret,"main pthread_mutex_lock");
    
    printf("I am main condition ok\n");
    sleep(5);
    //资源准备好 signal
    ret=pthread_cond_broadcast(&cond);
    THREAD_ERROR_CHECK(ret,"pthread_cond_broadcast");
    //解锁
    // ret=pthread_mutex_unlock(&lock);
    // THREAD_ERROR_CHECK(ret,"main pthread_mutex_unlock");
    //等A
    ret=pthread_join(thread_idA,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_joinA");
    //等B
    ret=pthread_join(thread_idB,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_joinB");
    //回收锁的资源
    ret=pthread_mutex_destroy(&lock);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_destroy");
    //销毁条件变量
    ret=pthread_cond_destroy(&cond);
    THREAD_ERROR_CHECK(ret,"pthread_cond_destroy");

    return 0;
}


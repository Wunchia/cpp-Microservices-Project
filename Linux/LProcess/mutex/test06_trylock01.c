#include <my_header.h>

pthread_mutex_t lock1;
pthread_mutex_t lock2;

void *thread_func(void *arg){
    int ret=pthread_mutex_lock(&lock2);
    THREAD_ERROR_CHECK(ret,"son pthread_mutex_lock2");

    printf("----\n");
    sleep(1);
    printf("----over\n");

    ret=pthread_mutex_trylock(&lock1);
    printf("ret : %d\n",ret);
    THREAD_ERROR_CHECK(ret,"son pthread_mutex_lock1");

    printf("I am son\n");

    ret=pthread_mutex_unlock(&lock1);
    THREAD_ERROR_CHECK(ret,"son pthread_mutex_unlock1");
    ret=pthread_mutex_unlock(&lock2);
    THREAD_ERROR_CHECK(ret,"son pthread_mutex_unlock2");

    pthread_exit((void*)NULL);
}

/*Usage: */
int main(int argc,char *argv[])
{
    //初始化互斥锁
    int ret=pthread_mutex_init(&lock1,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_init");
    
    ret=pthread_mutex_init(&lock2,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_init");

    //新建子线程
    pthread_t thread_id;
    ret=pthread_create(&thread_id,NULL,thread_func,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    
    ret=pthread_mutex_lock(&lock1);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_lock1");

    printf("++++\n");
    sleep(1);
    printf("++++over\n");

    ret=pthread_mutex_lock(&lock2);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_lock2");

    printf("I am main\n");

    ret=pthread_mutex_unlock(&lock2);
    THREAD_ERROR_CHECK(ret,"main pthread_mutex_lock2");

    ret=pthread_mutex_unlock(&lock1);
    THREAD_ERROR_CHECK(ret,"main pthread_mutex_lock1");

    //等待子进程结束
    ret=pthread_join(thread_id,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_join");

    //回收锁资源
    ret=pthread_mutex_destroy(&lock1);
    THREAD_ERROR_CHECK(ret,"pthread_destroy lock1");
    ret=pthread_mutex_destroy(&lock2);
    THREAD_ERROR_CHECK(ret,"pthread_destroy lock2");
    return 0;
}


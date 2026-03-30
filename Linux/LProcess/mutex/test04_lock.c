#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    pthread_mutex_t lock;

    //初始化互斥锁
    int ret=pthread_mutex_init(&lock,NULL);
    printf("ret : %d\n",ret);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_init");

    //上锁
    ret=pthread_mutex_lock(&lock);
    printf("ret : %d\n",ret);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_lock");

    //重要的代码

    //解锁
    ret=pthread_mutex_unlock(&lock);
    printf("ret : %d\n",ret);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_unlock");

    //回收锁的资源
    ret=pthread_mutex_destroy(&lock);
    printf("ret : %d\n",ret);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_destroy");

    return 0;
}


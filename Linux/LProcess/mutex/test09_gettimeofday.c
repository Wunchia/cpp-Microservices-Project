#include <my_header.h>
pthread_mutex_t lock;
int gCnt=0;

void *thread_func(void*arg){
    for(int idx=0;idx<1000000;idx++){
        // int ret=pthread_mutex_lock(&lock);
        // THREAD_ERROR_CHECK(ret,"pthread_mutex_lock");
        ++gCnt;
        // ret=pthread_mutex_unlock(&lock);
        // THREAD_ERROR_CHECK(ret,"pthread_mutex_unlock");
    }
    printf("I am son\n");
    pthread_exit(NULL);
}

/*Usage: */
int main(int argc,char *argv[])
{
    struct timeval beg,end;
    gettimeofday(&beg,NULL);

    //初始化互斥锁
    int ret=pthread_mutex_init(&lock,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_init");

    //新建子线程
    pthread_t thread_id;
    ret=pthread_create(&thread_id,NULL,thread_func,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_create");

    for(int idx=0;idx<1000000;++idx){
        // ret=pthread_mutex_lock(&lock);
        // THREAD_ERROR_CHECK(ret,"pthread_mutex_lock");
        ++gCnt;
        // ret=pthread_mutex_unlock(&lock);
        // THREAD_ERROR_CHECK(ret,"pthread_mutex_unlock");
    }

    printf("I am main\n");

    //等待子线程运行结束
    ret=pthread_join(thread_id,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    printf("gCnt:%d\n",gCnt);

    //回收锁的资源
    ret=pthread_mutex_destroy(&lock);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_destroy");

    gettimeofday(&end,NULL);
    printf("time : %ld\n",(end.tv_sec-beg.tv_sec)*1000000+(end.tv_usec-beg.tv_usec));

    return 0;
}


#include <my_header.h>
pthread_mutex_t lock;
int gCnt=0;

void *thread_func(void*arg){
    for(int idx=0;idx<1000000;idx++){
        int ret=pthread_mutex_lock(&lock);
        THREAD_ERROR_CHECK(ret,"pthread_mutex_lock");
        ++gCnt;
        ret=pthread_mutex_unlock(&lock);
        THREAD_ERROR_CHECK(ret,"pthread_mutex_unlock");
    }
    printf("I am son\n");
    pthread_exit(NULL);
}

/*Usage: */
int main(int argc,char *argv[])
{
    int ret=pthread_mutex_init(&lock,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_init");

    pthread_t thread_id;
    ret=pthread_create(&thread_id,NULL,thread_func,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_create");

    for(int idx=0;idx<1000000;++idx){
        ret=pthread_mutex_lock(&lock);
        THREAD_ERROR_CHECK(ret,"pthread_mutex_lock");
        ++gCnt;
        ret=pthread_mutex_unlock(&lock);
        THREAD_ERROR_CHECK(ret,"pthread_mutex_unlock");
    }

    printf("I am main\n");

    ret=pthread_join(thread_id,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    printf("gCnt:%d\n",gCnt);

    ret=pthread_mutex_destroy(&lock);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_destroy");

    return 0;
}


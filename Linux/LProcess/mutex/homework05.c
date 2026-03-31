#include <my_header.h>
pthread_mutex_t lock;
pthread_cond_t cond;
int status=0;
void*thread_func(void*arg){
    int ret=pthread_mutex_lock(&lock);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_lock");

    while(1!=status){
        ret=pthread_cond_wait(&cond,&lock);
        THREAD_ERROR_CHECK(ret,"pthread_cond_wait");
    }

    printf("Before B!\n");
    sleep(3);
    printf("After B\n");

    ret=pthread_mutex_unlock(&lock);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_unlock");

    pthread_exit((void*)NULL);
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
    THREAD_ERROR_CHECK(ret,"pthread_mutex_lock");

    printf("Before A!\n");
    sleep(3);
    printf("After A\n");

    status=1;

    ret=pthread_cond_signal(&cond);
    THREAD_ERROR_CHECK(ret,"pthread_cond_signal");

    ret=pthread_mutex_unlock(&lock);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_unlock");

    ret=pthread_join(thread_id,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_join");

    ret=pthread_mutex_destroy(&lock);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_destroy");

    ret=pthread_cond_destroy(&cond);
    THREAD_ERROR_CHECK(ret,"pthread_cond_destroy");

    return 0;
}


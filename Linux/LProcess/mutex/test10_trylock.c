#include <my_header.h>
pthread_mutex_t lock1;

void *thread_func(void *arg){
    int ret=0;
    while(1){
        //不断尝试申请lock1 直到拿到锁break
        ret=pthread_mutex_trylock(&lock1);
        if(0==ret){
            break;
        }
    }
    printf("I am son\n");
    ret=pthread_mutex_unlock(&lock1);
    THREAD_ERROR_CHECK(ret,"son pthread_mutex_unlock1");

    pthread_exit(NULL);
}
/*Usage: */
int main(int argc,char *argv[])
{
    int ret=pthread_mutex_init(&lock1,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_init");

    pthread_t thread_id;
    ret=pthread_create(&thread_id,NULL,thread_func,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_create");

    ret=pthread_mutex_lock(&lock1);
    THREAD_ERROR_CHECK(ret,"main pthread_mutex_lock1");

    sleep(50);
    printf("I am main\n");

    ret=pthread_mutex_unlock(&lock1);
    THREAD_ERROR_CHECK(ret,"main pthread_mutex_unlock1");

    ret=pthread_join(thread_id,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_join");

    ret=pthread_mutex_destroy(&lock1);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_destroy1");

    return 0;
}


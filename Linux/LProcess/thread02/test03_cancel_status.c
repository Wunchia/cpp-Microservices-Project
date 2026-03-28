#include <my_header.h>

void *thread_func(void * arg){
    while(1){
        pthread_testcancel();//cancel检查点
    }
    pthread_exit(NULL);
}

/*Usage: */
int main(int argc,char *argv[])
{
    pthread_t thread_id;
    int ret=pthread_create(&thread_id,NULL,thread_func,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_create");

    sleep(1);
    printf("I am main\n");

    ret=pthread_cancel(thread_id);//发出终止执行的信息
    printf("ret:%d\n",ret);
    THREAD_ERROR_CHECK(ret,"pthread_cancel");

    void*retval;//用于接收子线程终止执行时返回的状态信息
    ret=pthread_join(thread_id,&retval);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    printf("over\n");

    //#define PTHREAD_CANCELED ((void*)-1)
    if(retval==PTHREAD_CANCELED){
        printf("retval:%ld\n",(long)retval);
    }
    return 0;
}


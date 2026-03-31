#include <my_header.h>

void*thread_func(void*arg){
    printf("son thread id:%ld\n",pthread_self());
    pthread_exit((void*)NULL);
}

/*Usage:线程的属性设置
* 可以在创建线程之前给线程设置各种属性，比如：
* 1.让子线程与主线程分离（主线程不用再等子线程，不用主线程回收）
* 2.设置线程栈的大小
* 3.设置线程的调度策略 等等很多 */
int main(int argc,char *argv[])
{
    //线程的属性类型
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    //设置分离属性
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);

    pthread_t thread_id;
    //此时创建的子线程设置了分离属性
    int ret=pthread_create(&thread_id,&attr,thread_func,NULL);
    printf("ret : %d\n",ret);
    THREAD_ERROR_CHECK(ret,"pthread_create");

    sleep(1);
    printf("main thread_id : %ld\n",pthread_self());

    //此时再回收会报错 因为子线程已经与主线程分离
    ret=pthread_join(thread_id,NULL);
    printf("ret : %d\n",ret);
    THREAD_ERROR_CHECK(ret,"pthread_join");

    return 0;
}


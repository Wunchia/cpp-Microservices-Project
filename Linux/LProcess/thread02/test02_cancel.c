#include <my_header.h>

void* thread_func(void *arg){
    while(1){
        sleep(1);//sleep函数提供取消点
    }
    pthread_exit(NULL);
}

/*Usage: */
int main(int argc,char *argv[])
{
    pthread_t thread_id;
    int ret=pthread_create(&thread_id,NULL,thread_func,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_create");

    printf("I am main\n");

    sleep(1);
    ret=pthread_cancel(thread_id);
    printf("ret : %d\n",ret);//返回值为0，说明进行了cancel的动作
    //但子线程中如果没有取消点，就不会结束
    //子线程走到取消点，就会结束
    THREAD_ERROR_CHECK(ret,"pthread_cancel");

    ret=pthread_join(thread_id,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    printf("over\n");

    return 0;
}


#include <my_header.h>

void *thread_func(void *arg){
    char*pp=(char*)malloc(10);
    strcpy(pp,"hello");

    int fd=open("./Makefile",O_RDONLY);

    sleep(3);
    printf("son\n");

    free(pp);
    close(fd);
    printf("son cleaned\n");

    pthread_exit(NULL);
}

/*Usage: */
int main(int argc,char *argv[])
{
    pthread_t thread_id;
    int ret=pthread_create(&thread_id,NULL,thread_func,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    sleep(1);
    printf("main\n");

    //向子线程发出终止执行的信息 导致被通知的子线程被动终止
    //没能进行资源的清理 导致资源浪费
    ret=pthread_cancel(thread_id);
    printf("ret:%d\n",ret);
    THREAD_ERROR_CHECK(ret,"pthread_cancel");

    ret=pthread_join(thread_id,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    printf("over\n");

    return 0;
}


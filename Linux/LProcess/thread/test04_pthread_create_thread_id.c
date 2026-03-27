#include <my_header.h>
void *thread_func(void *arg){
    printf("*****son thread id:%ld\n",pthread_self());
    printf("I am son\n");
    return NULL;
}

/*Usage: */
int main(int argc,char *argv[])
{
    pthread_t thread_id;
    int ret=pthread_create(&thread_id,NULL,thread_func,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_create");

    printf("son thread id:%ld\n",thread_id);
    printf("main thread id:%ld\n",pthread_self());

    printf("I am main\n");
    while(1);
    return 0;
}


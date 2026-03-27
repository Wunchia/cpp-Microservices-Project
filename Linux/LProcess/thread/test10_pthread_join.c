#include <my_header.h>
void *thread_func(void* arg){
    printf("I am son\n");
    while(1);
    return NULL;
}

/*Usage: */
int main(int argc,char *argv[])
{
    pthread_t thread_id;

    int ret=pthread_create(&thread_id,NULL,thread_func,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    printf("I am main\n");

    pthread_join(thread_id,NULL);

    printf("over\n");

    return 0;
}


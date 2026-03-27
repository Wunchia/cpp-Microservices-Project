#include <my_header.h>
void *thread_func(void *arg){
    printf("I am son \n");

    int *pint=(int *)arg;
    *pint=30;
    return NULL;
}

/*Usage: */
int main(int argc,char *argv[])
{
    int num =10;
    pthread_t thread_id;
    int ret=pthread_create(&thread_id,NULL,thread_func,(void*)&num);
    THREAD_ERROR_CHECK(ret,"pthread_create");

    printf("I am main\n");
    sleep(5);

    printf("num : %d\n",num);

    return 0;
}


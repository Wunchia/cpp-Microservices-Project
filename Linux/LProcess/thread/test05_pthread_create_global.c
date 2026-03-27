#include <my_header.h>

long int gCnt=0;

void *thread_func(void *arg){
    for(int idx=0;idx<10000000000;++idx){
        ++gCnt;
    }
    printf("I am son\n");
    return NULL;
}
/*Usage: */
int main(int argc,char *argv[])
{
    pthread_t thread_id;
    int ret=pthread_create(&thread_id,NULL,thread_func,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_creat");

    for(int idx=0;idx<1000000000;++idx){
        ++gCnt;
    }

    printf("I am main\n");
    sleep(5);
    printf("gCnt=%ld\n",gCnt);
    return 0;
}


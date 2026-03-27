#include <my_header.h>

void *thread_func(void* arg){
    sleep(1);
    printf("I am son\n");
    int *pint=(int *)arg;
    *pint=30;
    printf("*pint=%d\n",*pint);
    return NULL;
}

void func(){
    int num=10;
    pthread_t thread_id;
    int ret=pthread_create(&thread_id,NULL,thread_func,(void*)&num);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    sleep(3);
}

int main(int argc,char* argv[]){
    func();
    printf("I am main\n");
    sleep(5);
    return 0;
}

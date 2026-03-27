#include <my_header.h>
#define THREAD_NUM 3

void* thread_func(void*arg){
    int id=*(int*)arg;
    free(arg);
    printf("%d have been created\n",id);
    int *status=(int*)malloc(sizeof(int));
    *status=100+id;
    printf("%d exiting, code =%d\n",id,*status);
    return (void*)status;
}

/*Usage: */
int main(int argc,char *argv[])
{
    pthread_t threads[THREAD_NUM];

    for(int i=0;i<THREAD_NUM;i++){
        int *arg=(int*)malloc(sizeof(int));
        *arg=i+1;
        int ret=pthread_create(&threads[i],NULL,thread_func,arg);
        THREAD_ERROR_CHECK(ret,"pthread_create");
        if(ret!=0){return -1;};
    }

    printf("created, waiting to join\n");

    for(int i=0;i<THREAD_NUM;i++){
        void*retval;
        if(pthread_join(threads[i],&retval)==0){
            int*status=(int*)retval;
            printf("main get code%d\n",*status);
            free(status);
        }else{
            printf("join %d failed\n",i+1);
        }
    }
    printf("all finished\n");
    return 0;
}


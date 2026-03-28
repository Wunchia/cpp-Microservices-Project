#include <my_header.h>

void func(){
    printf("func\n");
    long num=10;
    pthread_exit((void *)num);
    //long也是8字节，传出值可以被接到，且不涉及栈空间销毁后的段错误
    printf("++++++\n");
}

void *thread_func(void *arg){
    printf("I am son\n");
    func();
    printf("func over int thread_func\n");
    return NULL;
}

/*Usage: */
int main(int argc,char *argv[])
{
    pthread_t thread_id;
    int ret=pthread_create(&thread_id,NULL,thread_func,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    printf("I am main\n");

    void *retval;
    ret=pthread_join(thread_id,&retval);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    long pret=(long)retval;
    printf("main get the ret=%ld\n",pret);
    printf("over\n");
    return 0;
}

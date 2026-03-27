#include <my_header.h>
void *thread_func(void *arg){
    printf("I am son\n");
    char*pp=(char*)arg;
    strcpy(pp,"hello");
    return NULL;
}

/*Usage: */
int main(int argc,char *argv[])
{
    char *ptmp=(char*)malloc(10);

    pthread_t thread_id;
    int ret=pthread_create(&thread_id,NULL,thread_func,(void*)ptmp);
    THREAD_ERROR_CHECK(ret,"pthread_create");

    printf("I am main\n");
    sleep(5);
    printf("ptmp: %s\n",ptmp);

    free(ptmp);
    ptmp=NULL;
    return 0;
}


#include <my_header.h>
void *thread_func(void *arg){
    printf("I am son\n");
    return NULL;
}
/*Usage: */
int main(int argc,char *argv[])
{
    pthread_t thread_id;
    pthread_create(&thread_id,NULL,thread_func,NULL);
    printf("I am main\n");
    while(1);
    return 0;
}


#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
   sigset_t set,old;
   sigemptyset(&set);
   sigemptyset(&old);
   sigaddset(&set,SIGINT);
   sigprocmask(SIG_BLOCK,&set,&old);
   
   sleep(5);

   sigset_t pending;
   sigemptyset(&pending);
   sigpending(&pending);

   if(sigismember(&pending,SIGINT)){
    printf("2号信号未决\n");
   }

   sigprocmask(SIG_UNBLOCK,&set,&old);

    while(1);

    return 0;
}


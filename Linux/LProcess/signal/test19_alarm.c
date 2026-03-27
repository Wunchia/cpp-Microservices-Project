#include <my_header.h>
void func(int num){
    printf("num : %d\n",num);
    alarm(1);
}
/*Usage: */
int main(int argc,char *argv[])
{
    signal(SIGALRM,func);
    alarm(10);

    printf("while begin\n");
    while(1);
    printf("while over\n");
    return 0;
}


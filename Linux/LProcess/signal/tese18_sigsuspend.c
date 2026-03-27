#include <my_header.h>
void func(int num){
    printf("num : %d\n",num);
}

/*Usage: */
int main(int argc,char *argv[])
{
    signal(2,func);
    return 0;
}


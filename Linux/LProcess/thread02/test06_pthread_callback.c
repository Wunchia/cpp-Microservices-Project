#include <my_header.h>
int func(){
    printf("func\n");
    return 10;
}

int func2(){
    printf("func2\n");
    return 20;
}

/*Usage: */
int main(int argc,char *argv[])
{
    int (*pFunc)();
    pFunc=func;
    printf("1111\n");
    pFunc();
    printf("2222\n");

    pFunc=func2;
    printf("3333\n");
    pFunc();
    printf("4444\n");
    return 0;
}


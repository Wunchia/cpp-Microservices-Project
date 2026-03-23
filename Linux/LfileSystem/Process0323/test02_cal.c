#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    int num1,num2;
    sscanf(argv[1],"%d",&num1);
    sscanf(argv[2],"%d",&num2);
    printf("input num1=%d,num2=%d,sum=%d\n",num1,num2,(num1+num2));
    return 0;
}


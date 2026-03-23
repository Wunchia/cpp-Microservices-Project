#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    printf("test01_execl\n");
    execl("./test01_while","./test01_while","111","222",(void*)0);
    return 0;
}


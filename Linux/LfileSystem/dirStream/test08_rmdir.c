#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    int ret=rmdir("test07_md");
    ERROR_CHECK(ret,-1,"rmdir failed");

    return 0;
}


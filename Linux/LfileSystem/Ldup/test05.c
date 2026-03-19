#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    printf("%d\n",STDIN_FILENO);
    printf("%d\n",STDOUT_FILENO);
    printf("%d\n",STDERR_FILENO);
    printf("stdin->fileno=%d\n",stdin->_fileno);
    printf("fileno=%d\n",fileno(stdout));
    return 0;
}


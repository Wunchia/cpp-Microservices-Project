#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    int fd=open(argv[1],O_RDONLY);
    ERROR_CHECK(fd,-1,"fd open failed.");

    char*p=(char*)mmap(NULL,10,PROT_READ,MAP_SHARED,fd,0);
    ERROR_CHECK(p,MAP_FAILED,"mmap failed.");
    
    for(int i=0;i<100;i++){
        printf("%d-----\n",p[i]);
    }

    munmap(p,10);
    close(fd);
    
    return 0;
}


#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);
    int src_fd=open(argv[1],O_RDONLY);
    ERROR_CHECK(src_fd,-1,"open src failed.");

    int dest_fd=open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0666);
    ERROR_CHECK(dest_fd,-1,"open dest failed");

    char buf[4096]={0};
    ssize_t count=0;
    while((count=read(src_fd,buf,sizeof(buf)))!=0){
        write(dest_fd,buf,count);
    }

    close(src_fd);
    close(dest_fd);

    printf("copy finished\n");
    return 0;
}


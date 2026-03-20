#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    int read_fd=open("1.pipe",O_RDONLY);

    fd_set set;
    FD_ZERO(&set);
    FD_SET(STDIN_FILENO,&set);
    FD_SET(read_fd,&set);
    printf("select before.\n");

    int ret=select(read_fd+1,&set,NULL,NULL,NULL);
    printf("select over,ret=%d\n",ret);

    if(FD_ISSET(STDIN_FILENO,&set)){
        printf("stdin enable.\n");
        char buf[100]={0};
        read(STDIN_FILENO,buf,sizeof(buf));
        printf("stdin input:%s\n",buf);
    }

    if(FD_ISSET(read_fd,&set)){
        printf("pipe enabled.\n");
        char buf[100]={0};
        read(read_fd,buf,sizeof(buf));
        printf("pipe msg:%s\n",buf);
    }

    return 0;
}


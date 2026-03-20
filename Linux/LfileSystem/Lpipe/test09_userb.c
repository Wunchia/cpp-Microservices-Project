#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    printf("11111------\n");
    int w_fd=open("2.pipe",O_WRONLY);
    ERROR_CHECK(w_fd,-1,"usrb open 2.pipe failed");
    printf("22222-----\n");
    int r_fd=open("1.pipe",O_RDONLY);
    ERROR_CHECK(r_fd,-1,"usrb open 1.pipe failed");
    printf("33333-----\n");

    char content[]="msg from userb";
    write(w_fd,content,sizeof(content));

    char buf[100]={0};
    read(r_fd,buf,sizeof(buf));
    printf("usrb get msg:%s\n",buf);

    close(r_fd);
    close(w_fd);
    return 0;
}


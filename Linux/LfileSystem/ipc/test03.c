#include <my_header.h>
#include <bits/pthreadtypes.h>

/*Usage: */
int main(int argc,char *argv[])
{
    mkfifo("1.pipe",0600);
    pid_t ret=fork();

    if(ret==0){
        printf("child process open before\n");
        int fd =open("1.pipe",O_RDONLY);
        printf("child process open after\n");

        char buf[100]={0};
        read(fd,buf,sizeof(buf));
        printf("child process read buf:%s\n",buf);
        close(fd);
    }else{
        printf("father process sleep before\n");
        sleep(5);
        printf("father process sleep after(open before)\n");
        int fd=open("1.pipe",O_WRONLY);
        printf("father process open after\n");
        char content[]="msg from father process";
        write(fd,content,sizeof(content));
        close(fd);
    }

    unlink("1.pipe");
    return 0;
}


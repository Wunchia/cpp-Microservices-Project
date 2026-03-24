#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    int arr[2]={0};
    pipe(arr);
    pid_t ret=fork();
    if(ret==0){
        int write_fd=arr[1];
        char msg[]="msg from cccchild.";
        write(write_fd,msg,sizeof(msg));
    }else{
        int read_fd=arr[0];
        char buf[100]={0};
        read(read_fd,buf,sizeof(buf));
        printf("father process read from pipe:%s\n",buf);
    }
    return 0;
}


#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    int child_to_father_arr[2]={0};
    int father_to_child_arr[2]={0};

    pipe(child_to_father_arr);
    pipe(father_to_child_arr);

    pid_t ret=fork();
    if(ret==0){
        //父进程向子进程写 子进程从中读
        close(father_to_child_arr[1]);//禁掉子进程对这条匿名管道的写
        //子进程向父进程写 父进程从中读
        close(child_to_father_arr[0]);//禁掉子进程对这条匿名管道的读
                            
        int read_fd=father_to_child_arr[0];
        int write_fd=child_to_father_arr[1];

        char msg[]="hello from child";
        write(write_fd,msg,sizeof(msg));
        char buf[100]={0};
        read(read_fd,buf,sizeof(buf));
        printf("child process read from pipe:%s\n",buf);

        close(read_fd);
        close(write_fd);
    }else{
        int read_fd=child_to_father_arr[0];
        int write_fd=father_to_child_arr[1];

        char msg[]="hello from fatherrrr";
        write(write_fd,msg,sizeof(msg));

        char buf[100]={0};
        read(read_fd,buf,sizeof(buf));

        printf("father process read from pipe:%s\n",buf);

    }
    return 0;
}


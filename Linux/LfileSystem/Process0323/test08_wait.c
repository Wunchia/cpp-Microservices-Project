#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    if(fork()==0){
        printf("child process begin.\n");
        sleep(20);
        printf("child process over.\n");
        return 10;
    }else{
        printf("father process begin.\n");
        int wstatus;//用来接子进程的状态 是否正常退出
                    //正常退，退出码是多少？不正常退，信号标志是什么？
        // wait 会阻塞父进程
        // 它会等待子进程结束，并将结束状态写入 wstatus 指向的内存
        // 返回值 wait_ret 是结束的那个子进程的 PID
        pid_t wait_ret=wait(&wstatus);
        printf("father process over.\n");

        if(WIFEXITED(wstatus)){//正常退出  if exited
            printf("child status:%d\n",WEXITSTATUS(wstatus));
        }else if(WIFSIGNALED(wstatus)){//信号退出 if signaled
            printf("child signed:%d\n",WTERMSIG(wstatus));
        }
    }
    return 0;
}


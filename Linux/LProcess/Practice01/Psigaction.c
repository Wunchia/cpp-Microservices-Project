#include <my_header.h>

// int sigaction(
//     int signum,
//     const struct sigaction *act,
//     struct sigaction *oldact
// );

struct sigaction{
    void (*sa_handler)(int);
    void (*sa_sigaction)(int,siginfo_t*,void*);
    sigset_t sa_mask;
    int sa_flags;//指定信号处理的选项和标志
    void (*sa_restorer)(void);//过时，暂无用
};

sa_flags{
    SA_SIGINFO//使用sa_sigaction成员而不是sa_handler
    SA_RESETHAND//处理完捕获的信号后，信号处理回到默认（一次注册只生效一次）
    SA_NODEFER//在信号处理函数执行期间，同一个信号设置可以再次被触发
    SA_RESTART//被信号打断的系统调用自动重新调用
}

siginfo_t{
    pid_t si_pid;//发送进程的进程id
    sigval_t si_value;

}
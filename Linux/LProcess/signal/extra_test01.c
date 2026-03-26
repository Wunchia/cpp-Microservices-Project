#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

// 信号处理函数：当信号被“捕获”时运行
void my_handler(int sig) {
    printf("\n [Handler] 捕获到信号 %d (SIGINT)，正在处理...\n", sig);
}

int main() {
    sigset_t newmask, oldmask, waitmask;

    // 1. 设置信号处理函数
    // 当按下 Ctrl+C 时，执行 my_handler
    if (signal(SIGINT, my_handler) == SIG_ERR) {
        perror("signal error");
        exit(1);
    }

    // 2. 初始化信号集
    sigemptyset(&newmask);       // 清空 newmask
    sigaddset(&newmask, SIGINT); // 把 SIGINT (Ctrl+C) 加入“准备屏蔽”名单
    sigemptyset(&waitmask);      // waitmask 为空，表示 sigsuspend 期间不屏蔽任何信号

    // 3. 屏蔽 SIGINT（进入临界区）
    // 此时如果你狂按 Ctrl+C，信号会被内核“挂起”而不处理
    printf(">>> [步骤1] 屏蔽 SIGINT。请在接下来的 5 秒内狂按 Ctrl+C 试试...\n");
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
        perror("SIG_BLOCK error");
        exit(1);
    }

    // 模拟一段不想被中断的关键代码
    sleep(5); 
    printf(">>> [步骤2] 5 秒已到，关键任务完成。刚才按的 Ctrl+C 还在排队呢。\n");

    // 4. 使用 sigsuspend 原子性地挂起并等待
    // 这一步会：临时解开屏蔽 -> 睡眠等待信号 -> 捕获信号执行 handler -> 返回并恢复屏蔽
    printf(">>> [步骤3] 现在调用 sigsuspend() 等待刚才排队的信号...\n");
    
    // sigsuspend 总是返回 -1，并设置 errno 为 EINTR
    if (sigsuspend(&waitmask) != -1) {
        // 实际上这行代码永远不会执行，因为 sigsuspend 成功时一定是被中断返回 -1
    }

    printf(">>> [步骤4] sigsuspend 已返回。注意：此时 SIGINT 又是被屏蔽的状态了。\n");

    // 5. 彻底恢复最初的屏蔽状态（解开 SIGINT）
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
        perror("SIG_SETMASK error");
        exit(1);
    }

    printf(">>> [步骤5] 屏蔽彻底解除，程序正常退出。\n");

    return 0;
}

#include <my_header.h>
#include "thread_pool.h"
#include "socket.h"
#include "epoll.h"

int pipe_fd[2];

void func(int num){
    printf("signal:%d\n",num);
    write(pipe_fd[1],"1",1);
}

/*Usage: */
int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);

    //创建匿名管道
    pipe(pipe_fd);

    //创建子进程
    if(0!=fork()){
        //父进程在前台等待子进程结束
        //如果收到SIGINT 通过执行func通知子进程
        signal(SIGINT,func);
        wait(NULL);
        exit(0);
    }

    //子进程脱离当前进程组 避免因为SIGINT信号而被杀死
    setpgid(0,0);

    //拉起线程池
    thread_pool_t pool;
    init_thread_pool(&pool,4);

    //初始化socket
    int listen_fd=0;
    init_socket(&listen_fd,argv[1],argv[2]);

    //IO多路复用
    int epfd=epoll_create(1);
    ERROR_CHECK(epfd,-1,"epoll_create");

    add_epoll_fd(epfd,listen_fd);
    add_epoll_fd(epfd,pipe_fd[0]);

    while(1){
        //用户区维护数组准备拷贝就绪链表
        struct epoll_event lst[10];
        int nready=epoll_wait(epfd,lst,10,-1);
        ERROR_CHECK(nready,-1,"epoll_wait");
        printf("nready:%d\n",nready);

        for(int idx=0;idx<nready;++idx){
            //逐个处理就绪的fd
            int fd=lst[idx].data.fd;

            //如果是父进程发来 结束逻辑
            if(fd==pipe_fd[0]){
                char buf[10]={0};
                read(fd,buf,sizeof(buf));
                printf("man thread got front signal to exit\n");

                pthread_mutex_lock(&pool.lock);
                pool.exitFlag=1;//通知子线程处理完了就结束
                //广播告知条件满足 唤醒在等事件的空闲子线程
                pthread_cond_broadcast(&pool.cond);
                pthread_mutex_unlock(&pool.lock);

                //逐个等结束
                for(int idx=0;idx<pool.thread_num;++idx){
                    pthread_join(pool.thread_id_arr[idx],NULL);
                }
                //子线程全部结束 自己也结束
                pthread_exit((void*)NULL);
            }

            //如果是文件就绪 传输逻辑
            if(fd==listen_fd){
                int conn_fd=accept(listen_fd,NULL,NULL);
                ERROR_CHECK(conn_fd,-1,"accept");

                //把连好的连接放进队列 让子线程去处理
                pthread_mutex_lock(&pool.lock);
                enQueue(&pool.queue,conn_fd);
                pthread_cond_signal(&pool.cond);//唤醒一个来干活
                pthread_mutex_unlock(&pool.lock);
            }
        }
    }

    return 0;
}


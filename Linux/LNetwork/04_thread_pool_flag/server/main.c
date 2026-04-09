#include <my_header.h>
#include "thread_pool.h"
#include "socket.h"
#include "epoll.h"

int pipe_fd[2];

//打印传入的int(信号)  并向管道写端写入一个"1"
void func(int num){
    printf("num : %d\n",num);
    write(pipe_fd[1],"1",1);
}

/*Usage: */
int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);

    pipe(pipe_fd);

    if(fork()!=0){
        //父进程
        signal(2,func);//将信号2 SIGINT重定向到func
        wait(NULL);//父进程等待子进程运行结束进行清理 避免僵尸进程
        exit(0);
    }

    //子进程 父进程在上面的if里就exit了 走不到这

    //让子进程脱离进程组 自立门户
    setpgid(0,0);

    //子进程拉起线程池
    thread_pool_t pool;
    init_thread_pool(&pool,4);

    //初始化socket
    int listen_fd=0;
    init_socket(&listen_fd,argv[1],argv[2]);

    //IO多路复用
    int epfd=epoll_create(1);
    ERROR_CHECK(epfd,-1,"epoll_create");

    //将监听的socket文件描述符挂入红黑树
    add_epoll_fd(epfd,listen_fd);
    
    //将管道的读端挂入红黑树  
    //如果这里就绪，说明父进程收到了信号，往管道里写了东西
    add_epoll_fd(epfd,pipe_fd[0]);

    while(1){

        //用户区维护数组用于拷贝就绪队列
        struct epoll_event lst[10];
        int nready=epoll_wait(epfd,lst,10,-1);
        ERROR_CHECK(nready,-1,"epoll_wait");
        printf("nready:%d\n",nready);

        //取出就绪文件 进行操作
        for(int idx=0;idx<nready;++idx){
            int fd=lst[idx].data.fd;

            //收到信号 结束进程
            if(fd==pipe_fd[0]){
                char buf[10]={0};
                read(fd,buf,sizeof(buf));
                printf("son's main got the father's signal\n");

                pthread_mutex_lock(&pool.lock);
                pool.exitFlag=1;//将标志位置为1
                //标志位重置和广播条件变量的就绪放在同一个锁里原子执行
                pthread_cond_broadcast(&pool.cond);
                pthread_mutex_unlock(&pool.lock);

                for(int idx=0;idx<pool.thread_num;++idx){
                    pthread_join(pool.thread_id_arr[idx],NULL);
                }
                //子线程全部退出后 子进程的主线程也退出
                pthread_exit((void*)NULL);
            }

            //监听的文件就绪
            if(fd==listen_fd){
                //取出就绪链接，用conn_fd维护链接
                int conn_fd=accept(listen_fd,NULL,NULL);
                ERROR_CHECK(conn_fd,-1,"accept");

                //上锁
                pthread_mutex_lock(&pool.lock);
                //入队 让线程池的线程进行处理
                enQueue(&pool.queue,conn_fd);
                pthread_cond_signal(&pool.cond);

                pthread_mutex_unlock(&pool.lock);
            }
        }
    }

    return 0;
}


#include <my_header.h>
#include "thread_pool.h"
#include "socket.h"
#include "epoll.h"

int pipe_fd[2];

void func(int signal){
    printf("signal:%d\n",signal);
    write(pipe_fd[1],"1",1);
}

/*Usage: */
int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);

    pipe(pipe_fd);

    if(0!=fork()){
        signal(SIGINT,func);
        wait(NULL);
        exit(0);
    }

    setpgid(0,0);

    thread_pool_t pool;
    init_thread_pool(&pool,4);

    int listen_fd=0;
    init_socket(&listen_fd,argv[1],argv[2]);

    int epfd=epoll_create(1);
    ERROR_CHECK(epfd,-1,"epoll_create");

    add_epoll_ctl(epfd,listen_fd);
    add_epoll_ctl(epfd,pipe_fd[0]);

    while(1){
        struct epoll_event lst[10];
        int nready=epoll_wait(epfd,lst,10,-1);
        ERROR_CHECK(nready,-1,"epoll_wait");
        printf("nready:%d\n",nready);

        for(int idx=0;idx<nready;++idx){
            int fd=lst[idx].data.fd;

            if(fd==pipe_fd[0]){
                char buf[10]={0};
                read(fd,buf,sizeof(buf));
                printf("main thread got front signal to exit\n");

                pthread_mutex_lock(&pool.lock);
                pool.exitFlag=1;

                pthread_cond_broadcast(&pool.cond);
                pthread_mutex_unlock(&pool.lock);

                for(int idx=0;idx<pool.thread_num;++idx){
                    pthread_join(pool.thread_id_arr[idx],NULL);
                }

                pthread_exit((void*)NULL);
            }

            if(fd==listen_fd){
                int conn_fd=accept(listen_fd,NULL,NULL);
                ERROR_CHECK(conn_fd,-1,"accept");

                pthread_mutex_lock(&pool.lock);
                enQueue(&pool.queue,conn_fd);
                pthread_cond_signal(&pool.cond);
                pthread_mutex_unlock(&pool.lock);
            }
        }
    }

    return 0;
}


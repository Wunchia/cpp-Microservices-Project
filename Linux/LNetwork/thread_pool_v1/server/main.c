#include <my_header.h>
#include "thread_pool.h"
#include "socket.h"
#include "worker.h"
/*Usage: */
int main(int argc,char *argv[])
{
    thread_pool_t pool;
    init_thread_pool(&pool,3);

    int listen_fd=0;
    init_socket(&listen_fd,"192.168.171.128","8080");
    // init_socket(&socket_fd,argv[1],argv[2]);

    int epfd=epoll_create(1);
    ERROR_CHECK(epfd,-1,"epoll_create");
    add_epoll_fd(epfd,listen_fd);

    while(1){
        struct epoll_event lst[10];
        int nready=epoll_wait(epfd,lst,10,-1);

        for(int idx=0;idx<nready;++idx){
            int fd=lst[idx].data.fd;
            
            if(fd==listen_fd){
                int conn_fd=accept(listen_fd,NULL,NULL);
                ERROR_CHECK(conn_fd,-1,"accept");

                pthread_mutex_lock(&pool.pool_lock);
                enQueue(&pool.queue,conn_fd);
                //只要向队列中放了文件描述符
                //用signal唤醒一个进程
                //让工作线程取出文件描述符
                pthread_cond_signal(&pool.cond);
                pthread_mutex_unlock(&pool.pool_lock);
            }
        }
    }

    return 0;
}


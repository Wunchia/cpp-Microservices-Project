#include <my_header.h>
#include "thread_pool.h"
/*Usage: */
int main(int argc,char *argv[])
{
    pool_t pool;
    initPool(&pool,3);

    int socket_fd;
    initTcpSocket(&socket_fd,"192.168.171.128","8080");

    int epoll_fd=epoll_create(1);
    epoll_addfd(epoll_fd,socket_fd);

    while(1){
        struct epoll_event list[1024];
        int epoll_num=epoll_wait(epoll_fd,list,1024,-1);

        for(int i=0;i<epoll_num;i++){
            if(list[i].data.fd==socket_fd){
                int net_fd=accept(socket_fd,NULL,NULL);

                pthread_mutex_lock(&pool.pool_lock);
                enQueue(&pool.queue,net_fd);
                pthread_cond_signal(&pool.cond);
                pthread_mutex_unlock(&pool.pool_lock);
            }
        }
    }

    return 0;
}


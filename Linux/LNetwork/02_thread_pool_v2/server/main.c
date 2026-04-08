#include <my_header.h>
#include "epoll.h"
#include "queue.h"
#include "socket.h"
#include "thread_pool.h"

/*Usage: */
int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);
    
    //拉起线程池 拉一堆打工仔等活
    thread_pool_t pool;
    init_thread_pool(&pool,4);
    
    //建立socket端口 开始监听
    int listen_fd=0;
    //传参获得ip和端口号
    init_socket(&listen_fd,argv[1],argv[2]);
    
    //IO多路复用 创建struct eventpoll对象 返回给epfd
    int epfd=epoll_create(1);
    ERROR_CHECK(epfd,-1,"epoll_create");

    //epoll_ctl 将listen_fd挂进epfd对应对象内的红黑树
    add_epoll_fd(epfd,listen_fd);

    while(1){

        //在用户区维护数组 以备拷贝就绪链表内的struct eventpoll对象
        struct epoll_event lst[10];
        //wait被唤醒后 拷入用户区维护的数组
        int nready=epoll_wait(epfd,lst,10,-1);
        ERROR_CHECK(nready,-1,"epoll_wait");
        printf("nready:%d\n",nready);

        for(int idx=0; idx < nready; ++idx){
            //取出就绪的文件描述符 方便之后书写
            int fd=lst[idx].data.fd;

            if(fd==listen_fd){
                //accept 接收一条全链接(已完成三次握手) 
                //将链接关联到文件描述符conn_fd
                int conn_fd=accept(listen_fd,NULL,NULL);
                ERROR_CHECK(conn_fd,-1,"accept");

                //----------------------------------------
                //将就绪的fd放入队列 线程池里的线程就开始工作了
                //开始操作前先上锁
                pthread_mutex_lock(&pool.lock);
                //将监听到的已就绪的 conn_fd 入队
                enQueue(&pool.queue,conn_fd);
                //唤醒条件变量
                pthread_cond_signal(&pool.cond);

                //操作完成 解锁
                pthread_mutex_unlock(&pool.lock);
                //-----------------------------------------
            }
        }
    }

    return 0;
}


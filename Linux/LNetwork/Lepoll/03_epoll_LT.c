#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    //水平触发是默认模式
    int epfd=epoll_create(1);
    ERROR_CHECK(epfd,-1,"epoll_create");

    struct epoll_event evt;
    evt.events=EPOLLIN;//监听读事件
    evt.data.fd=STDIN_FILENO;

    int ret=epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&evt);
    ERROR_CHECK(ret,-1,"epoll_ctl add");

    while(1){
        //对于水平触发而言，只要文件描述符可读
        //（在这里就是缓冲区中有数据）
        //那么，就一直可读，直到将缓冲区中的数据读空
        struct epoll_event lst[2];
        int nready=epoll_wait(epfd,lst,2,-1);
        ERROR_CHECK(nready,-1,"epoll_wait");
        printf("nready:%d\n",nready);

        for(int idx=0;idx<nready;++idx){
            int fd=lst[idx].data.fd;

            if(fd==STDIN_FILENO){
                char buf[2]={0};
                int cnt=read(fd,buf,sizeof(buf));
                ERROR_CHECK(cnt,-1,"read");
                //int cnt=recv(fd,buf,sizeof(buf),0);
                printf("cnt=%d,buf:%s\n",cnt,buf);
            }
        }
    }
    return 0;
}


#include <my_header.h>

void add_epoll_fd(int epfd,int fd){
    struct epoll_event evt;
    evt.events=EPOLLIN;
    evt.data.fd=fd;

    int ret=epoll_ctl(epfd,EPOLL_CTL_ADD,fd,&evt);
    ERROR_CHECK(ret,-1,"epoll_ctl add");
}

void del_epoll_fd(int epfd,int fd){
    struct epoll_event evt;
    evt.events=EPOLLIN;
    evt.data.fd=fd;

    int ret=epoll_ctl(epfd,EPOLL_CTL_DEL,fd,&evt);
    ERROR_CHECK(ret,-1,"epoll_ctl del");
}

/*Usage: */
int main(int argc,char *argv[])
{
    char *ip="192.168.171.128";
    char *port="12345";

    int listen_fd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(listen_fd,-1,"socket");

    int opt=1;
    int ret=setsockopt(listen_fd,SOL_SOCKET,SO_REUSEPORT,&opt,sizeof(opt));
    ERROR_CHECK(ret,-1,"setsockopt");

    struct sockaddr_in addr;
    memset(&addr,0,sizeof(addr));

    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=inet_addr(ip);
    addr.sin_port=htons(atoi(port));

    ret=bind(listen_fd,(struct sockaddr*)&addr,sizeof(addr));
    ERROR_CHECK(ret,-1,"bind");

    ret=listen(listen_fd,10);
    ERROR_CHECK(ret,-1,"listen");

    printf("server is listening\n");

    int epfd=epoll_create(1);
    ERROR_CHECK(epfd,-1,"epoll_create");

    add_epoll_fd(epfd,listen_fd);

    int conn_fd=0;
    int client_fds[100]={0};
    int client_count=0;

    while(1){
        struct epoll_event lst[10];

        int nready=epoll_wait(epfd,lst,10,-1);
        ERROR_CHECK(nready,-1,"epoll_wait");
        printf("---nready:%d---\n",nready);

        for(int idx=0;idx<nready;++idx){
            int fd=lst[idx].data.fd;//取出就绪的fd，便于之后书写
            if(fd==listen_fd){
                conn_fd=accept(listen_fd,NULL,NULL);
                ERROR_CHECK(conn_fd,-1,"accept");

                add_epoll_fd(epfd,conn_fd);
                client_fds[client_count++]=conn_fd;
            }else{
                char buf[50]={0};
                int cnt=recv(fd,buf,sizeof(buf),0);
                if(0==cnt){
                    printf("client %d closed\n",fd);
                    for(int i=0;i<client_count;i++){
                        if(client_fds[i]==fd){
                            client_fds[i]=client_fds[client_count-1];
                            client_count--;
                        }
                    }
                    del_epoll_fd(epfd,fd);
                    close(fd);
                    continue;
                }
                for(int pos=0;pos<client_count;++pos){
                    int client_fd=client_fds[pos];
                    if(client_fd==fd){
                        continue;
                    }
                    ret=send(client_fd,buf,cnt,0);
                    ERROR_CHECK(ret,-1,"send");
                }

            }//else conn_fd

        }//for idx

    }//while

    close(listen_fd);
    close(conn_fd);
    return 0;
}

#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    char *ip="192.168.171.128";
    char *port="12345";
    
    int listen_fd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(listen_fd,-1,"socket");

    int opt=1;
    int ret=setsockopt(listen_fd,SOL_SOCKET,SO_REUSEPORT,&opt,sizeof(opt));

    struct sockaddr_in addr,client_addr;
    memset(&addr,0,sizeof(addr));
    socklen_t len=sizeof(client_addr);
    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=inet_addr(ip);
    addr.sin_port=htons(atoi(port));

    //绑定ip、端口号和listen_fd
    ret=bind(listen_fd,(struct sockaddr*)&addr,sizeof(addr));
    ERROR_CHECK(ret,-1,"bind");

    //监听
    ret=listen(listen_fd,10);
    ERROR_CHECK(ret,-1,"listen");

    printf("server is listening\n");

    int conn_fd=0;
    fd_set set;
    FD_ZERO(&set);

    FD_SET(listen_fd,&set);//将listen_fd监听端口放入位图

    while(1){
        fd_set tmp;
        tmp=set;
        int nready=select(10,&tmp,NULL,NULL,NULL);
        ERROR_CHECK(nready,-1,"select");
        printf("----nready:%d----\n",nready);

        //全链接队列中存在就绪消息 存在已完成三次握手的链接
        if(FD_ISSET(listen_fd,&tmp)){
            conn_fd=accept(listen_fd,(struct sockaddr*)&client_addr,&len);
            ERROR_CHECK(conn_fd,-1,"accept");

            FD_SET(conn_fd,&set);
            FD_SET(STDIN_FILENO,&set);

            FD_CLR(listen_fd,&set);
        }

        //服务器在自己终端上输入 向客户端传递消息
        if(FD_ISSET(STDIN_FILENO,&tmp)){
            char buf[50]={0};
            read(STDIN_FILENO,buf,sizeof(buf));
            send(conn_fd,buf,strlen(buf),0);
        }

        //客户端发来消息
        if(FD_ISSET(conn_fd,&tmp)){
            char buf[50]={0};
            int cnt=recv(conn_fd,buf,sizeof(buf),0);
            ERROR_CHECK(cnt,-1,"recv");
            printf("---\nrecv cnt:%d\n",cnt);
            if(0==cnt){
                printf("client closed\n---\n");
                FD_CLR(conn_fd,&set);
                FD_CLR(STDIN_FILENO,&set);
                FD_SET(listen_fd,&set);
                close(conn_fd);
                continue;
            }
            printf("msg:%s\n---\n",buf);
        }
    }

    close(listen_fd);
    close(conn_fd);
    return 0;
}


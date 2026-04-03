#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    char*ip="192.168.171.128";
    char *port="12345";

    int listen_fd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(listen_fd,-1,"socket");

    int opt=1;
    int ret=setsockopt(listen_fd,SOL_SOCKET,SO_REUSEPORT,&opt,sizeof(opt));
    ERROR_CHECK(ret,-1,"setsockopt");

    struct sockaddr_in addr,client_addr;
    socklen_t len=sizeof(client_addr);

    memset(&addr,0,sizeof(addr));

    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=inet_addr(ip);
    addr.sin_port=htons(atoi(port));

    ret=bind(listen_fd,(struct sockaddr*)&addr,sizeof(addr));
    ERROR_CHECK(ret,-1,"bind");

    ret=listen(listen_fd,10);
    ERROR_CHECK(ret,-1,"listen");
    printf("server is listening\n");

    int conn_fd=accept(listen_fd,(struct sockaddr*)&client_addr,&len);
    ERROR_CHECK(conn_fd,-1,"accept");

    //----------数据传输阶段-------------

    fd_set set;
    FD_ZERO(&set);

    while(1){
        FD_SET(STDIN_FILENO,&set);
        FD_SET(conn_fd,&set);

        int nready=select(10,&set,NULL,NULL,NULL);
        ERROR_CHECK(nready,-1,"select");
        printf("---nready:%d---\n",nready);

        if(FD_ISSET(STDIN_FILENO,&set)){
            char buf[50]={0};
            read(STDIN_FILENO,buf,sizeof(buf));
            ret=send(conn_fd,buf,strlen(buf),0);
            ERROR_CHECK(ret,-1,"send");
        }

        if(FD_ISSET(conn_fd,&set)){
            char buf[50]={0};
            int cnt=recv(conn_fd,buf,sizeof(buf),0);
            ERROR_CHECK(cnt,-1,"recv");
            if(0==cnt){
                printf("client closed\n");
                break;
            }
            printf("----\nrecv cnt:%d\nmsg:%s\n----\n",cnt,buf);
        }
    }
    //--------------数据传输阶段结束------------------

    close(listen_fd);
    close(conn_fd);

    return 0;
}


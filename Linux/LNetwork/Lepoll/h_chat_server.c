#include <my_header.h>

typedef struct conn{
    int fd;
    int alive;
}conn_t;

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

    struct sockaddr_in addr,client_addr;
    socklen_t len=sizeof(client_addr);
    memset(&addr,0,sizeof(addr));
    memset(&client_addr,0,sizeof(client_addr));

    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=inet_addr(ip);
    addr.sin_port=htons(atoi(port));

    ret=bind(listen_fd,(struct sockaddr*)&addr,sizeof(addr));
    ERROR_CHECK(ret,-1,"bind");

    ret=listen(listen_fd,10);
    ERROR_CHECK(ret,-1,"listen");

    printf("server is listening\n");

    conn_t conn_arr[100]={0};
    int size=0;

    fd_set set;
    FD_ZERO(&set);
    FD_SET(listen_fd,&set);

    while(1){
        fd_set tmp;
        tmp=set;

        int nready=select(100,&tmp,NULL,NULL,NULL);
        ERROR_CHECK(nready,-1,"select");
        printf("---nready:%d---\n",nready);

        if(FD_ISSET(listen_fd,&tmp)){
            int conn_fd=accept(listen_fd,(struct sockaddr*)&client_addr,&len);
            ERROR_CHECK(conn_fd,-1,"accept");

            FD_SET(conn_fd,&set);

            conn_arr[size].fd=conn_fd;
            conn_arr[size].alive=1;
            size++;
        }

        for(int idx=0;idx<size;++idx){
            int fd=conn_arr[idx].fd;
            if(FD_ISSET(fd,&tmp)){
                char buf[50]={0};

                int cnt=recv(fd,buf,sizeof(buf),0);
                ERROR_CHECK(cnt,-1,"recv");
                if(0==cnt){
                    printf("client %d closed\n",fd);
                    conn_arr[idx].fd=0;
                    conn_arr[idx].alive=0;
                    FD_CLR(fd,&set);
                    close(fd);
                }
                //不为0 则群发
                for(int pos=0;pos<size;++pos){
                    if(0==conn_arr[pos].alive||pos==idx){
                        continue;
                    }
                    ret=send(conn_arr[pos].fd,buf,strlen(buf),0);
                    ERROR_CHECK(ret,-1,"send");
                }
            }
        }
    }
    close(listen_fd);
    return 0;
}


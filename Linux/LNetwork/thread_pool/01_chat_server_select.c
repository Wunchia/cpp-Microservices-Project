#include <my_header.h>

typedef struct conn{
    int fd;//文件描述符
    int alive;//连接是不是存活的 活着就是1 挂了就是0
}conn_t;

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

    struct sockaddr_in addr;
    memset(&addr,0,sizeof(addr));

    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=inet_addr(ip);
    addr.sin_port=htons(atoi(port));

    ret=bind(listen_fd,(struct sockaddr*)&addr,sizeof(addr));
    ERROR_CHECK(ret,-1,"bind");

    ret=listen(listen_fd,10);
    ERROR_CHECK(ret,-1,"listen");

    conn_t con_arr[100]={0};
    int size=0;

    fd_set set;
    FD_ZERO(&set);
    FD_SET(listen_fd,&set);

    while(1){
        fd_set tmp;
        tmp=set;

        int nready=select(100,&tmp,NULL,NULL,NULL);
        ERROR_CHECK(nready,-1,"select");
        printf("nready:%d\n",nready);

        //监听到新用户连入 则创建conn_fd 放入con_arr[]维护
        if(FD_ISSET(listen_fd,&tmp)){
            int conn_fd=accept(listen_fd,NULL,NULL);
            ERROR_CHECK(conn_fd,-1,"accept");

            con_arr[size].fd=conn_fd;
            con_arr[size].alive=1;
            ++size;

            FD_SET(conn_fd,&set);
        }

        //通信
        for(int idx=0;idx<size;++idx){
            //从数组中取出其中的值
            int fd=con_arr[idx].fd;

            if(FD_ISSET(fd,&tmp)){
                char buf[50]={0};
                int cnt=recv(fd,buf,sizeof(buf),0);
                ERROR_CHECK(cnt,-1,"recv");
                if(0==cnt){
                    printf("client %d closed\n",fd);
                    
                    con_arr[idx].fd=0;
                    con_arr[idx].alive=0;

                    FD_CLR(fd,&set);
                    close(fd);

                    continue;
                }
                //转发给其他用户
                for(int i=0;i<size;i++){
                    if(0==con_arr[i].alive||i==idx){
                        continue;
                    }
                    send(con_arr[i].fd,buf,strlen(buf),0);
                }
            }
        }
    }

    close(listen_fd);

    return 0;
}


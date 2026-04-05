#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    char*ip="192.168.171.128";
    char*port="12345";

    int listen_fd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(listen_fd,-1,"socket");

    int opt=1;
    int ret=setsockopt(listen_fd,SOL_SOCKET,SO_REUSEPORT,&opt,sizeof(opt));

    struct sockaddr_in addr,client_addr;
    memset(&addr,0,sizeof(addr));
    memset(&client_addr,0,sizeof(client_addr));
    socklen_t len=sizeof(client_addr);

    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=inet_addr(ip);
    addr.sin_port=htons(atoi(port));

    ret=bind(listen_fd,(struct sockaddr*)&addr,sizeof(addr));
    ERROR_CHECK(ret,-1,"bind");

    ret=listen(listen_fd,10);
    ERROR_CHECK(ret,-1,"listen");

    printf("server is listening\n");

    //将不同用户的对应conn_fd用数组管理起来
    int arr[1024];
    for(int idx=0;idx<1024;++idx){
        arr[idx]=0;
    }//初始化

    int conn_fd=0;

    fd_set set;
    FD_ZERO(&set);
    FD_SET(listen_fd,&set);

    FD_SET(STDIN_FILENO,&set);

    while(1){
        fd_set tmp;
        tmp=set;

        int nready=select(10,&tmp,NULL,NULL,NULL);
        ERROR_CHECK(conn_fd,-1,"select");
        printf("----nready:%d----\n",nready);

        //监听 维护用户链接
        if(FD_ISSET(listen_fd,&tmp)){
            conn_fd=accept(listen_fd,(struct sockaddr*)&client_addr,&len);
            ERROR_CHECK(conn_fd,-1,"accept");

            FD_SET(conn_fd,&set);

            for(int idx=0;idx<1024;++idx){
                if(0==arr[idx]){
                    arr[idx]=conn_fd;
                    break;
                }
            }
        }

        //通信

        //服务端向客户端广播发送
        if(FD_ISSET(STDIN_FILENO,&tmp)){
            char buf[50]={0};
            read(STDIN_FILENO,buf,sizeof(buf));
            for(int idx=0;idx<1024;++idx){
                if(arr[idx]>0){
                    send(arr[idx],buf,strlen(buf),0);
                }
            }
        }

        for(int idx=0;idx<1024;++idx){
            if(0==arr[idx]){
                continue;
            }

            if(FD_ISSET(arr[idx],&tmp)){
                char buf[50]={0};

                int cnt=recv(arr[idx],buf,sizeof(buf),0);
                ERROR_CHECK(cnt,-1,"recv");
                printf("---\nrecv cnt:%d\n",cnt);
                if(0==cnt){
                    printf("client closed\n---\n");
                    FD_CLR(arr[idx],&set);
                    close(arr[idx]);
                    arr[idx]=0;
                    continue;
                }
                for(int i=0;i<1024;++i){
                    if(arr[i]>0&&i!=idx){
                        send(arr[i],buf,strlen(buf),0);
                    }
                }
                printf("msg:%s\n---\n--boardcasted--\n",buf);
            }
        }
    }

    close(listen_fd);
    close(conn_fd);
    return 0;

}


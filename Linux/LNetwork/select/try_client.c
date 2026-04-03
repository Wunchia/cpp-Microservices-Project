#include <my_header.h>

/*Usage: */
int main(int argc, char *argv[])
{
    char *ip = "192.168.171.128";
    char *port = "12345";

    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(listen_fd, -1, "socket");

    // 绑定服务器的ip与端口号
    struct sockaddr_in addr;

    memset(&addr, 0, sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(atoi(port));

    int ret=connect(listen_fd,(struct sockaddr*)&addr,sizeof(addr));
    ERROR_CHECK(ret,-1,"connect");

    fd_set set;
    FD_ZERO(&set);

    // 让程序保持运行 避免一次收发后就结束
    while (1)
    {
        FD_SET(listen_fd, &set);
        FD_SET(STDIN_FILENO, &set);

        int nready=select(10,&set,NULL,NULL,NULL);
        ERROR_CHECK(nready,-1,"select");
        printf("nready:%d\n",nready);

        if(FD_ISSET(STDIN_FILENO,&set)){
            char buf[50]={0};
            read(STDIN_FILENO,buf,sizeof(buf));
            int res_send=send(listen_fd,buf,strlen(buf),0);
            ERROR_CHECK(res_send,-1,"send");
            printf("\n");
        }

        if(FD_ISSET(listen_fd,&set)){
            char buf[50]={0};
            int cnt=recv(listen_fd,buf,sizeof(buf),0);
            ERROR_CHECK(cnt,-1,"recv");
            if(0==cnt){
                break;
            }
            printf("recv cnt:%d\n",cnt);
            write(STDOUT_FILENO,buf,sizeof(buf));
            printf("\n");
        }
    }

    close(listen_fd);

    return 0;
}

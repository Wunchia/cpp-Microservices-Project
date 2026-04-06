#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    char*ip="192.168.171.128";
    char*port="12345";

    int client_fd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(client_fd,-1,"socket");

    struct sockaddr_in addr;

    memset(&addr,0,sizeof(addr));

    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=inet_addr(ip);
    addr.sin_port=htons(atoi(port));

    int ret=connect(client_fd,(struct sockaddr*)&addr,sizeof(addr));
    ERROR_CHECK(ret,-1,"connect");

    fd_set set;

    while(1){

        FD_ZERO(&set);
        FD_SET(STDIN_FILENO,&set);
        FD_SET(client_fd,&set);

        int nready=select(10,&set,NULL,NULL,NULL);
        ERROR_CHECK(nready,-1,"select");
        printf("----nready:%d----\n",nready);

        if(FD_ISSET(STDIN_FILENO,&set)){
            char buf[50]={0};
            ssize_t sret=read(STDIN_FILENO,buf,sizeof(buf));
            if(sret>0){
                send(client_fd,buf,strlen(buf),0);
            }
        }

        if(FD_ISSET(client_fd,&set)){
            char buf[50]={0};
            int cnt=recv(client_fd,buf,sizeof(buf),0);
            ERROR_CHECK(cnt,-1,"recv");
            printf("---\nrecv cnt:%d\n",cnt);
            if(0==cnt){
                printf("server closed\n---\n");
                break;
            }
            printf("msg:%s\n---\n",buf);
        }
    }
    close(client_fd);
    return 0;
}


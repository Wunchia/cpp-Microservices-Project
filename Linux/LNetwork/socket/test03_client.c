#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    char *ip="192.168.171.128";
    char*port="12345";
    //创建文件描述符
    int listen_fd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(listen_fd,-1,"socket");

    //绑定服务器的ip与端口号
    struct sockaddr_in server_addr;
    // socklen_t len=sizeof(client_addr);
    memset(&server_addr,0,sizeof(server_addr));//初始化addr

    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=inet_addr(ip);//本机字节序转为网络字节序
    server_addr.sin_port=htons(atoi(port));

    //使用connect函数进行三次握手
    int ret=connect(listen_fd,(struct sockaddr*)&server_addr,sizeof(server_addr));
    ERROR_CHECK(ret,-1,"connect");

    //客户端给服务端发送数据
    int cnt=send(listen_fd,"hello from client",20,0);
    printf("read cnt:%d\n",cnt);

    //客户端接收服务端发送的数据
    char buf[100]={0};
    cnt=recv(listen_fd,buf,sizeof(buf),0);
    printf("recv cnt:%d\n",cnt);
    printf("client buf:%s\n",buf);

    while(1);

    //关闭文件描述符（意味着执行了四次挥手）
    close(listen_fd);
    return 0;
}


#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    char *ip="192.168.171.128";
    char*port="12345";
    //创建文件描述符
    int listen_fd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(listen_fd,-1,"socket");

    //设置端口重用
    int opt=1;
    setsockopt(listen_fd,SOL_SOCKET,SO_REUSEPORT,&opt,sizeof(opt));

    //绑定服务器的ip与端口号
    struct sockaddr_in server_addr,client_addr;
    socklen_t len=sizeof(client_addr);

    memset(&server_addr,0,sizeof(server_addr));//初始化addr

    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=inet_addr(ip);//本机字节序转为网络字节序
    server_addr.sin_port=htons(atoi(port));

    //绑定端口号
    int ret=bind(listen_fd,(struct sockaddr*)&server_addr,sizeof(server_addr));
    ERROR_CHECK(ret,-1,"bind");

    //监听
    ret=listen(listen_fd,10);//10是全链接队列的大小
    ERROR_CHECK(ret,-1,"listen");

    //从全链接队列中取出一个
    int conn_fd=accept(listen_fd,(struct sockaddr*)&client_addr,&len);
    // accept(listen_fd,NULL,NULL);//不想知晓客户端的ip和端口号时
    ERROR_CHECK(conn_fd,-1,"accept");

    //服务端接收客户端发送的数据
    char buf[100]={0};
    int cnt=recv(conn_fd,buf,sizeof(buf),0);
    printf("recv cnt:%d\n",cnt);
    printf("server buf:%s\n",buf);

    //服务端给客户端发送数据
    cnt=send(conn_fd,"hello from server",20,0);
    printf("read cnt:%d\n",cnt);

    while(1);

    close(listen_fd);
    close(conn_fd);
    return 0;
}


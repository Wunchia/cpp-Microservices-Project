#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    char*ip="192.168.171.128";
    char*port="12345";

    int listen_fd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(listen_fd,-1,"socket");

    //设置端口重用
    int opt=1;
    int ret=setsockopt(listen_fd,SOL_SOCKET,SO_REUSEPORT,&opt,sizeof(opt));
    ERROR_CHECK(ret,-1,"setsockopt");

    struct sockaddr_in addr,client_addr;
    socklen_t len=sizeof(client_addr);

    memset(&addr,0,sizeof(addr));

    addr.sin_family=AF_INET;//ipv4
    addr.sin_addr.s_addr=inet_addr(ip);//本机字节序转为网络字节序
    addr.sin_port=htons(atoi(port));//字符串转int再转网络字节序 16bit

    //绑定socket和ip、端口号
    ret=bind(listen_fd,(struct sockaddr*)&addr,sizeof(addr));//用sockaddr_in再强制类型转换为sockaddr
    ERROR_CHECK(ret,-1,"bind");

    //监听端口
    ret=listen(listen_fd,10);//10为全链接队列长度
    ERROR_CHECK(ret,-1,"listen");
    printf("server is listening\n");

    sleep(5);

    //取一个已建立的链接 后两个参数返回客户端ip和port 不需要时可填NULL
    int conn_fd=accept(listen_fd,(struct sockaddr*)&client_addr,&len);
    ERROR_CHECK(conn_fd,-1,"accept");

    //--------数据传输阶段-----------
    //收
    char buf[100]={0};
    int cnt=recv(conn_fd,buf,sizeof(buf),0);
    printf("-----\nrecv cnt=%d\n",cnt);
    printf("msg: %s\n-----\n",buf);

    //发
    cnt=send(conn_fd,"test from server",16,0);
    printf("\n---send cnt:%d---\n",cnt);
    //-------数据传输阶段结束-------

    sleep(5);

    close(listen_fd);
    close(conn_fd);//四次挥手

    return 0;
}


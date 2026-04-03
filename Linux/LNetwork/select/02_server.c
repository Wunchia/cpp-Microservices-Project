#include <my_header.h>

/*Usage: 可持续双向传递消息，但无法正常关闭，任意一方断掉链接会导致另一方死循环*/
int main(int argc,char *argv[])
{
    char*ip="192.168.171.128";
    char*port="12345";

    //创建socket
    int listen_fd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(listen_fd,-1,"socket");

    //设置端口重用
    int opt=1;
    int ret=setsockopt(listen_fd,SOL_SOCKET,SO_REUSEPORT,&opt,sizeof(opt));

    //存放ip、端口号
    struct sockaddr_in addr,client_addr;
    socklen_t len=sizeof(client_addr);

    memset(&addr,0,sizeof(addr));

    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=inet_addr(ip);
    addr.sin_port=htons(atoi(port));

    //将socket绑定到ip和端口
    ret=bind(listen_fd,(struct sockaddr*)&addr,sizeof(addr));
    ERROR_CHECK(ret,-1,"bind");

    //监听网络端口
    ret=listen(listen_fd,10);
    ERROR_CHECK(ret,-1,"listen");

    printf("server is listening\n");

    //取出一个已完成握手的链接
    int conn_fd=accept(listen_fd,(struct sockaddr*)&addr,&len);
    ERROR_CHECK(conn_fd,-1,"accept");

//--------------数据传输阶段-----------------
    //定义位图 使用select同时监听标准输入和网络端口 实现消息持续收发
    fd_set set;
    FD_ZERO(&set);

    while(1){
        FD_SET(STDIN_FILENO,&set);//将标准输入置入位图
        FD_SET(conn_fd,&set);//将网络端口置入位图

        int nready=select(10,&set,NULL,NULL,NULL);//监听IO就绪情况
        ERROR_CHECK(nready,-1,"select");
        printf("---nready:%d---\n",nready);

        //如果标准输入就绪 则读入缓冲后发往网络端口
        if(FD_ISSET(STDIN_FILENO,&set)){
            char buf[50]={0};
            read(STDIN_FILENO,buf,sizeof(buf));

            send(conn_fd,buf,sizeof(buf),0);
        }

        //如果网络端口就绪 则接收信息后向屏幕打印
        if(FD_ISSET(conn_fd,&set)){
            char buf[50]={0};
            int cnt=recv(conn_fd,buf,sizeof(buf),0);
            printf("----\nrecv cnt:%d\n",cnt);
            printf("msg:%s\n----\n",buf);
        }
    }
//------------数据传输阶段结束--------------

    close(listen_fd);
    close(conn_fd);//四次挥手

    return 0;
}


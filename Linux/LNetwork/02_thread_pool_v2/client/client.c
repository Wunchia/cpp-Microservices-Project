#include <my_header.h>

int main(int argc, char *argv[])
{
    char *ip = "192.168.171.128";
    char *port = "12345";

    //创建文件描述符
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(listen_fd, -1, "socket");

    //绑定服务器的ip与端口号
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));//初始化addr

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);//本机字节序转换为网络字节序
    addr.sin_port = htons(atoi(port));

    //调用connect函数进行三次握手
    int ret = connect(listen_fd, (struct sockaddr *)&addr, sizeof(addr));
    ERROR_CHECK(ret, -1, "connect");
    //---------------走到这里就是客户端的socket的代码---------
    //-走到这里就说明三次握手已经建立成功了，同时可以与服务器传输数据-

    //接收文件名的长度
    int file_name_len=0;
    recv(listen_fd,&file_name_len,sizeof(int),MSG_WAITALL);
    
    //接收文件名
    char file_name[60]={0};
    recv(listen_fd,file_name,file_name_len,MSG_WAITALL);
    
    //接收文件大小
    off_t file_size=0;
    recv(listen_fd,&file_size,sizeof(off_t),MSG_WAITALL);
    printf("file_size:%ld\n",file_size);

    //接收服务器发送过来的数据  此时会用到前面接收的文件名
    int file_fd=open(file_name,O_RDWR|O_CREAT,0600);
    ftruncate(file_fd,file_size);

    char *p=(char*)mmap(NULL,file_size,PROT_READ|PROT_WRITE,MAP_SHARED,file_fd,0);
    recv(listen_fd,p,file_size,MSG_WAITALL);

    munmap(p,file_size);

    close(file_fd);
    close(listen_fd);
    return 0;
}
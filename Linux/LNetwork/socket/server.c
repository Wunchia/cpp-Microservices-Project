#include <my_header.h>

/*Usage: */
int main(int argc, char *argv[])
{
    char *ip = "192.168.171.128";
    char *port = "12345";

    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(listen_fd, -1, "socket");

    int opt = 1;
    int ret = setsockopt(listen_fd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt));
    ERROR_CHECK(ret, -1, "setsockopt");

    struct sockaddr_in addr, client_addr;
    socklen_t len = sizeof(client_addr);

    memset(&addr, 0, sizeof(addr));
    memset(&client_addr, 0, sizeof(client_addr));

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(atoi(port));

    ret = bind(listen_fd, (struct sockaddr*)&addr, sizeof(addr));
    ERROR_CHECK(ret, -1, "bind");

    ret =listen(listen_fd,10);
    ERROR_CHECK(ret,-1,"listen");

    int conn_fd=accept(listen_fd,(struct sockaddr*)&client_addr,&len);
    ERROR_CHECK(conn_fd,-1,"accept");

    char buf[100]={0};
    int cnt=recv(conn_fd,buf,sizeof(buf),0);
    ERROR_CHECK(cnt,-1,"recv");
    printf("recv cnt:%d\n",cnt);
    printf("server buf:%s\n",buf);

    cnt=send(conn_fd,"server",7,0);
    ERROR_CHECK(cnt,-1,"send");
    printf("send cnt:%d\n",cnt);

    sleep(10);

    close(listen_fd);
    close(conn_fd);

    return 0;
}

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

    // 绑定服务器的ip与端口号
    struct sockaddr_in addr, client_addr;
    socklen_t len = sizeof(client_addr);

    memset(&addr, 0, sizeof(addr));
    memset(&client_addr, 0, sizeof(client_addr));

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(atoi(port));

    ret = bind(listen_fd, (struct sockaddr *)&addr, sizeof(addr));
    ERROR_CHECK(ret, -1, "bind");

    ret = listen(listen_fd, 10);
    ERROR_CHECK(ret, -1, "listen");

    int conn_fd=0;
    conn_fd = accept(listen_fd, (struct sockaddr *)&client_addr, &len);
    ERROR_CHECK(conn_fd, -1, "accept");

    fd_set set;
    FD_ZERO(&set);

    // 最开始只需要将listen_fd监听起来，只要这个文件描述符就绪（可读）才可以取链接
    FD_SET(listen_fd, &set);

    // 让程序保持运行 避免一次收发后就结束
    while (1)
    {
        fd_set tmp; // 临时的位图，在select之前设置需要监听的文件描述符
                    // 因为select中位图是一个传入传出参数，有可能会改了之前位图的结果
        tmp = set;
        int nready = select(10, &tmp, NULL, NULL, NULL);
        ERROR_CHECK(nready, -1, "select");
        printf("nready : %d\n", nready);

        //监听listen，看是否有有新的链接到达
        if (FD_ISSET(listen_fd, &tmp))
        {
            conn_fd = accept(listen_fd, NULL, NULL);
            ERROR_CHECK(conn_fd, -1, "accept");
            FD_SET(conn_fd, &set);
            FD_SET(STDIN_FILENO, &set);
            //不想监听其他新的链接，那么就可以将listen_fd从set中清除
            FD_CLR(listen_fd,&set);
        }

        if (FD_ISSET(STDIN_FILENO, &set))
        {
            char buf[50] = {0};
            read(STDIN_FILENO, buf, sizeof(buf));
            int res_send = send(conn_fd, buf, strlen(buf), 0);
            ERROR_CHECK(res_send, -1, "send");
            printf("\n");
        }

        if (FD_ISSET(conn_fd, &set))
        {
            char buf[50] = {0};
            int cnt = recv(conn_fd, buf, sizeof(buf), 0);
            ERROR_CHECK(cnt, -1, "recv");
            if (0 == cnt)
            {
                FD_CLR(conn_fd,&tmp);
                //再将服务器在终端输入的操作禁止掉，不让其发给已经断开的链接
                FD_CLR(STDIN_FILENO,&tmp);
                //继续监听listen，让其他客户端能继续链接到服务器
                FD_SET(listen_fd,&tmp);

                close(conn_fd);
                continue;
            }
            write(STDOUT_FILENO, buf, sizeof(buf));
            printf("\n");
        }
    }

    close(listen_fd);
    close(conn_fd);

    return 0;
}

#include <muduo/base/Logging.h>
#include <muduo/base/Timestamp.h>
#include <muduo/net/Callbacks.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>

using namespace muduo::net;
using namespace muduo;

void onConnection(const TcpConnectionPtr& conn)
{
    // 记录日志
    LOG_INFO << "DaytimeServer - " << conn->peerAddress().toIpPort() << " -> "
             << conn->localAddress().toIpPort() << " is "
             << (conn->connected() ? "UP" : "DOWN");

    if (conn->connected()) {
        conn->send(Timestamp::now().toFormattedString() + "\n");
        // conn->shutdown(); // 服务器关闭写端，进入到半连接状态
        conn->forceClose(); // 关闭连接
    }
}

void onMessage(
    const TcpConnectionPtr& conn, // TCP连接
    Buffer* buf, // 用户态缓冲区：数据已经读到Buffer中
    Timestamp ts) // 时间戳：数据到达的时间戳
{
    string msg(buf->retrieveAllAsString());
    LOG_INFO << conn->name() << " discards " << msg.size()
             << " bytes received at " << ts.toString();
}

int main()
{
    // 1. 创建事件循环 (epoll实例)
    EventLoop loop;

    // 2. 创建套接字地址 （封装套接字地址：struct sockaddr_in）
    InetAddress addr(8888);

    // 3. 创建Tcp服务器: 创建监听套接字
    TcpServer server(&loop, addr, "daytime");
    // 注册回调函数 (Tcp编程的三个半事件)
    server.setConnectionCallback(onConnection); // 连接建立和连接关闭
    server.setMessageCallback(onMessage); // 有数据到达
    // server.setWriteCompleteCallback(); // 半个事件：发送数据完毕

    // 4. 启动服务器：将监听套接字放入epoll实例中
    server.start();

    // 5. 事件循环
    loop.loop();
}

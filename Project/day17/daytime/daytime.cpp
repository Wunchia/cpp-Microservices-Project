#include <muduo/base/Logging.h>
#include <muduo/base/Timestamp.h>
#include <muduo/net/Callbacks.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/TcpServer.h>

using namespace muduo;
using namespace muduo::net;

//====回调函数1：连接建立/断开时被调用
void onConnection(const TcpConnectionPtr& conn){
    LOG_INFO << conn->peerAddress().toIpPort() << " -> "
             << conn->localAddress().toIpPort() << " is "
             << (conn->connected() ? "UP" : "DOWN");

    if(conn->connected()){
        conn->send(Timestamp::now().toFormattedString()+"\n");
        conn->forceClose();//发完主动关闭 短连接
    }
}

void onMessage(const TcpConnectionPtr& conn,
               Buffer* buf,
               Timestamp ts)
{
    string msg(buf->retrieveAllAsString());
    LOG_INFO<<conn->name()<<"discards"<<msg.size()<<"bytes";
}

int main(int argc,char *argv[])
{
    EventLoop loop;//创建事件循环
    InetAddress addr(8848);//监听地址
    TcpServer server(&loop,addr,"daytime");//创建TCP服务器

    server.setConnectionCallback(onConnection);//注册回调
    server.setMessageCallback(onMessage);

    server.start();
    loop.loop();

    return 0;
}

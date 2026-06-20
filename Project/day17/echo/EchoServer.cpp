#include "EchoServer.h"
#include <muduo/base/CurrentThread.h>
#include <muduo/base/Logging.h>
#include <muduo/base/Timestamp.h>
#include <muduo/net/Buffer.h>
#include <muduo/net/Callbacks.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/TcpServer.h>

using namespace muduo;
using namespace muduo::net;


EchoServer::EchoServer(EventLoop* loop,const InetAddress& listenAddr)
:_server(loop,listenAddr,"EchoServer")
{
    _server.setConnectionCallback(
        std::bind(&EchoServer::onConnection,this,_1)
    );

    _server.setMessageCallback(
        std::bind(&EchoServer::onMessage,this,_1,_2,_3)
    );

    _server.setThreadNum(4);
}

void EchoServer::start(){
    _server.start();
}


// 回调1：连接事件
void EchoServer::onConnection(const TcpConnectionPtr& conn){
    LOG_INFO << conn->peerAddress().toIpPort() << " -> "
    << conn->localAddress().toIpPort() << " is "
    << (conn->connected() ? "UP" : "DOWN");
}

// 回调2：消息事件
void EchoServer::onMessage(const TcpConnectionPtr& conn,
    Buffer* buf,Timestamp time)
{
    string msg(buf->retrieveAllAsString());
    LOG_INFO<<conn->name()<<" echo "<<msg.size()<<" bytes";
    conn->send(msg); //原样发送回客户端
}

int main(int argc,char *argv[])
{
    EventLoop loop;
    InetAddress addr(8848);
    EchoServer server(&loop,addr);
    server.start();
    loop.loop();

    return 0;
}

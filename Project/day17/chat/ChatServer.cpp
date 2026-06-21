#include "ChatServer.h"
#include "LengthHeaderCodec.h"
#include <muduo/base/Logging.h>
#include <muduo/base/Timestamp.h>
#include <muduo/net/Callbacks.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <string>

using namespace muduo;
using namespace muduo::net;

ChatServer::ChatServer(EventLoop* loop,const InetAddress& listenAddr)
    :_server(loop, listenAddr, "ChatServer")
    ,_codec(std::bind(&ChatServer::onEntireMessage, this,_1,_2,_3))
{
    // 注册连接回调
    _server.setConnectionCallback(
        std::bind(&ChatServer::onConnection,this,_1)
    );

    // 注册消息回调
    _server.setMessageCallback(
        std::bind(&LengthHeaderCodec::onMessage,&_codec,_1,_2,_3)
    );

    _server.setThreadNum(4);
}

void ChatServer::start(){
    _server.start();
    LOG_INFO<<"ChatServer started on port"<<_server.ipPort();
}

void ChatServer::onConnection(const TcpConnectionPtr& conn){
    if(conn->connected()){
        _connections.insert(conn);
        LOG_INFO<<conn->peerAddress().toIpPort()
                <<" -> "<<conn->localAddress().toIpPort()
                <<" is UP, total connections: "<<_connections.size();

        // 发送欢迎消息，告知当前在线人数
        string welcome="Welcome to chat room! Current online users: "
            +std::to_string(_connections.size());
        _codec.send(conn,welcome);
    }else{
        _connections.erase(conn);
        LOG_INFO<<conn->peerAddress().toIpPort()
                <<" is DOWN, remaining connections: "
                <<_connections.size();
    }
}

void ChatServer::onEntireMessage(const TcpConnectionPtr& conn,
    const string& message, Timestamp receiveTime)
{
    string formattedMsg=receiveTime.toFormattedString()+" : "+message;
    LOG_INFO<<"Broadcasting: "<<formattedMsg;

    for(const auto& c:_connections){
        if(c!=conn){
            _codec.send(c,formattedMsg);
        }
    }
}

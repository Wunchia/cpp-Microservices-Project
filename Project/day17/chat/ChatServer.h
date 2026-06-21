#pragma once

#include "LengthHeaderCodec.h"
#include <muduo/base/Timestamp.h>
#include <muduo/net/Callbacks.h>
#include <muduo/net/TcpServer.h>
#include <set>

class ChatServer{
public:
    ChatServer(muduo::net::EventLoop* loop,
        const muduo::net::InetAddress& listenAddr);
    void start();

private:
    void onConnection(const muduo::net::TcpConnectionPtr& conn);
    void onEntireMessage(const muduo::net::TcpConnectionPtr& conn,
        const std::string& message,
        muduo::Timestamp receiveTime);

    muduo::net::TcpServer _server;
    LengthHeaderCodec _codec;
    std::set<muduo::net::TcpConnectionPtr> _connections;
};

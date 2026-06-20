#pragma once
#include <muduo/base/Timestamp.h>
#include <muduo/net/Buffer.h>
#include <muduo/net/Callbacks.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/TcpConnection.h>
#include <muduo/net/TcpServer.h>

class EchoServer
{
public:
    EchoServer(muduo::net::EventLoop* loop,
        const muduo::net::InetAddress& listenAddr);
    void start();

private:
    void onConnection(const muduo::net::TcpConnectionPtr& conn);

    void onMessage(const muduo::net::TcpConnectionPtr& conn,
        muduo::net::Buffer* buf,
        muduo::Timestamp time);

    muduo::net::TcpServer _server;
};

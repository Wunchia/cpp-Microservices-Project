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
    EchoServer(muduo::net::EventLoop* loop,const muduo::net::InetAddress& listenAddr)
    :_server(loop,listenAddr,"EchoServer")
    {
        //TODO: 注册回调函数
    }
    void start(){
        _server.start();
    }

private:
    static void onConnect

private:
    muduo::net::TcpServer _server;
};

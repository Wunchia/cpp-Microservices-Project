#include <muduo/base/Logging.h>
#include <muduo/base/Timestamp.h>
#include <muduo/net/Buffer.h>
#include <muduo/net/Callbacks.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/TcpConnection.h>
#include <muduo/net/TcpServer.h>
#include <functional>
#include <endian.h>

using namespace muduo;
using namespace muduo::net;

class LengthHeaderCodec{
public:
    using MessageCallback=std::function<void (const TcpConnectionPtr&,
        const std::string&,Timestamp)>;

    LengthHeaderCodec(const MessageCallback& cb):_callback(cb){}

    //编码 发送
    void send(const TcpConnectionPtr& conn,const std::string&msg){
        Buffer buf;
        uint32_t len = htobe32(msg.size());
        buf.append(&len,sizeof(len));
        buf.append(msg.data(),msg.size());
        conn->send(&buf);
    }

    //解码 处理粘包
    void onMessage(const TcpConnectionPtr& conn,
        Buffer* buf,Timestamp ts){
            while(buf->readableBytes()>=4){
                const void*data=buf->peek();
                uint32_t len=be32toh(*static_cast<const uint32_t*>(data));
                if(buf->readableBytes()<4+len){break;}
                buf->retrieve(4);
                std::string msg(buf->peek(),len);
                buf->retrieve(len);
                _callback(conn,msg,ts);
            }
        }

private:
    MessageCallback _callback;
};

//======Echo 服务器（用编解码器）========
class EchoServer{
public:
    EchoServer(EventLoop* loop,const InetAddress& addr)
    :_server(loop,addr,"EchoWithCodec"),
     _codec(std::bind(&EchoServer::onMessage,this,_1,_2,_3))
     {
         _server.setConnectionCallback(
             std::bind(&EchoServer::onConnection,this,_1)
         );
         _server.setMessageCallback(
             std::bind(&LengthHeaderCodec::onMessage,&_codec,_1,_2,_3)
         );
         _server.setThreadNum(4);
     }

     void start(){
         _server.start();
     }

private:
    void onConnection(const TcpConnectionPtr& conn){
        LOG_INFO<<(conn->connected()?"UP":"DOWN");
    }

    void onMessage(const TcpConnectionPtr& conn,
        const std::string& msg,Timestamp ts){
            LOG_INFO<<"received: "<<msg;
            _codec.send(conn, msg);
        }

    TcpServer _server;
    LengthHeaderCodec _codec;
};

int main(int argc,char *argv[])
{
    EventLoop loop;
    InetAddress addr(8848);
    EchoServer server(&loop,addr);
    server.start();
    loop.loop();
    return 0;
}

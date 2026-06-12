#include <SimpleAmqpClient/BasicMessage.h>
#include <SimpleAmqpClient/SimpleAmqpClient.h>
#include <locale>
#include <string.h>

using namespace std;
using namespace AmqpClient;

int main(int argc,char *argv[])
{
    //创建channel
    string host="127.0.0.1";
    int port=5672;
    string username="guest";
    string password="guest";
    string vhost="/";
    Channel::ptr_t channel=Channel::Create(host,port,username,password,vhost);

    //构建消息
    BasicMessage::ptr_t message=BasicMessage::Create("Hello RabbitMQ");

    //发送消息
    string exchange="oss.direct";//交换机
    string routingKey="oss";//消息的routingKey
    channel->BasicPublish(exchange,routingKey,message);//发布消息
    return 0;
}

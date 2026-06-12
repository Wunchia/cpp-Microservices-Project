#include <SimpleAmqpClient/Envelope.h>
#include <SimpleAmqpClient/SimpleAmqpClient.h>
#include <string>
#include <iostream>

using namespace std;
using namespace AmqpClient;

int main(int argc,char *argv[])
{
    //以URL的方式创建Channel
    string uri="amqp://guest:guest@localhost:5672/%2f";
    Channel::ptr_t channel=Channel::CreateFromUri(uri);

    //获取消息
    // 1.拉取模式
    // const string& q="queue1";
    // Envelope::ptr_t envelope;
    // channel->BasicGet(envelope,q);
    // if(envelope&&envelope->Message()){
    //     cout<<envelope->Message()->Body()<<endl;
    // }

    // 2.推送模式
    const string& q="queue1";
    channel->BasicConsume(q);//订阅队列
    //阻塞：等待RAbbitMQ推送消息
    Envelope::ptr_t envelope=channel->BasicConsumeMessage();
    //打印消息
    if(envelope && envelope->Message()){
        cout<<envelope->Message()->Body()<<endl;
    }

    return 0;
}

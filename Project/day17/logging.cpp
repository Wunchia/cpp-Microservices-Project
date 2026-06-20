#include <muduo/base/Logging.h>

int main(int argc,char *argv[])
{
    muduo::Logger::setLogLevel(muduo::Logger::TRACE);

    LOG_TRACE<<"trace:最低级别，追踪信息";
    LOG_DEBUG<<"debug:调试信息";
    LOG_INFO<<"info：服务器启动，端口8848";
    LOG_WARN<<"warn：磁盘使用率超过80%";
    LOG_ERROR<<"error：连接数据库失败";

    return 0;
}

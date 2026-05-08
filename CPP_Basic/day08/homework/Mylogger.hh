#ifndef __MYLOGGER_HH__
#define __MYLOGGER_HH__

#include <log4cpp/Category.hh>
#include <string>

#define addPrefix(msg)(std::string("<") + __FILE__ + ":" \
    + std::to_string(__LINE__) + " "+ std::string(__FUNCTION__) + "> " + msg).c_str()

#define LogDebug(msg) MyLogger::getInstance()->debug(addPrefix(msg))
#define LogInfo(msg) MyLogger::getInstance()->info(addPrefix(msg))
#define LogWarn(msg) MyLogger::getInstance()->warn(addPrefix(msg))
#define LogError(msg) MyLogger::getInstance()->error(addPrefix(msg))

class MyLogger{
public:
    static MyLogger* getInstance();
    static void destroyInstance();

    MyLogger(const MyLogger&)=delete;
    MyLogger& operator=(const MyLogger&)=delete;

    void debug(const char*msg);
    void info(const char*msg);
    void warn(const char*msg);
    void error(const char*msg);

private:
    MyLogger();
    ~MyLogger();

    static MyLogger* ms_instance;
    log4cpp::Category & m_category;
};

#endif
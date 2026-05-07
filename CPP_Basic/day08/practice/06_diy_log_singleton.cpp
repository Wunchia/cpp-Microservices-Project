#include <iostream>
#include <string>
#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/Appender.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/PatternLayout.hh>

#define MY_LOG(category, priority, msg) \
    category.priority(std::string("[") + __FILE__ + ":" \
    + std::to_string(__LINE__) + " " + __FUNCTION__ + "] " + msg)

#define LogDebug(msg) MY_LOG((*MyLogger::getInstance()),debug,msg)
#define LogInfo(msg) MY_LOG((*MyLogger::getInstance()),info,msg)
#define LogWarn(msg) MY_LOG((*MyLogger::getInstance()),warn,msg)
#define LogError(msg) MY_LOG((*MyLogger::getInstance()),error,msg)
using std::cin;
using std::cout;
using std::endl;
using std::string;

class MyLogger{
public:
    static MyLogger*getInstance(){
        if(_pInstance==nullptr){
            _pInstance=new MyLogger();
        }
        return _pInstance;
    }

    static void destroy(){
        if(_pInstance){
            log4cpp::Category::shutdown();
            delete _pInstance;
            _pInstance=nullptr;
        }
    }

    void debug(const std::string& msg){_root.debug(msg);}
    void info(const std::string& msg){_root.info(msg);}
    void warn(const std::string& msg){_root.warn(msg);}
    void error(const std::string& msg){_root.error(msg);}

private:
    MyLogger()
    :_root(log4cpp::Category::getRoot())
    {
        log4cpp::PatternLayout* pLayout=new log4cpp::PatternLayout();
        pLayout->setConversionPattern("%d [%p] %c: %m%n");

        log4cpp::OstreamAppender* pOsApp=new log4cpp::OstreamAppender("console",&cout);
        pOsApp->setLayout(pLayout);

        _root.setPriority(log4cpp::Priority::DEBUG);
        _root.addAppender(pOsApp);
    }

    MyLogger(const MyLogger& rhs)=delete;
    MyLogger&operator=(const MyLogger&rhs)=delete;

    ~MyLogger(){}

    static MyLogger* _pInstance;
    log4cpp::Category& _root;
};

MyLogger* MyLogger::_pInstance=nullptr;

void test(){
    LogInfo("test info");
    LogError("test error");
}

int main(int argc,char *argv[])
{
    test(); 
    return 0;
}


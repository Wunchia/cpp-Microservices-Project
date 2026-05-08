#include "Mylogger.hh"
#include <iostream>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/Priority.hh>

MyLogger* MyLogger::ms_instance=nullptr;

MyLogger* MyLogger::getInstance(){
    if(ms_instance==nullptr){
        ms_instance=new MyLogger();
    }
    return ms_instance;
}

void MyLogger::destroyInstance(){
    if(ms_instance){
        delete ms_instance;
        ms_instance=nullptr;
    }
}

MyLogger::MyLogger()
:m_category(log4cpp::Category::getRoot().getInstance("MyCategory"))
{
    //设置布局
    log4cpp::PatternLayout* pLayout1=new log4cpp::PatternLayout();
    pLayout1->setConversionPattern("%d [%p] %m%n");

    log4cpp::PatternLayout* pLayout2=new log4cpp::PatternLayout();
    pLayout2->setConversionPattern("%d [%p] %m%n");

    //设置输出器
    log4cpp::OstreamAppender* pOsApp=new log4cpp::OstreamAppender("console",&std::cout);
    pOsApp->setLayout(pLayout1);

    log4cpp::RollingFileAppender* pRollApp=new log4cpp::RollingFileAppender("rollingFile","roll.log");
    pRollApp->setLayout(pLayout2);

    //配置 Category
    m_category.setPriority(log4cpp::Priority::DEBUG);
    m_category.addAppender(pOsApp);
    m_category.addAppender(pRollApp);

}

MyLogger::~MyLogger(){
    log4cpp::Category::shutdown();
}

void MyLogger::debug(const char*msg){m_category.debug(msg);}
void MyLogger::info(const char*msg){m_category.info(msg);}
void MyLogger::warn(const char*msg){m_category.warn(msg);}
void MyLogger::error(const char*msg){m_category.error(msg);}
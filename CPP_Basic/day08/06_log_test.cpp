#include <iostream>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/Category.hh>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using namespace log4cpp;

void test1(){
    // 创建输出器对象
    OstreamAppender* appender1= new OstreamAppender("console",&cout);

    // 给输出器绑定格式化器对象
    PatternLayout* layout1=new PatternLayout{};
    //setConversionPattern(diy格式)
    layout1->setConversionPattern("%d [%p] %c : %m%n");
    //绑定
    appender1->setLayout(layout1);

    // 获取根记录器
    Category &root=Category::getRoot();

    // 设置优先级
    root.setPriority(Priority::INFO);

    // 给记录器添加输出器
    root.addAppender(appender1);

    // 产生日志信息
    root.debug("debug msg....");
    root.info("info msg....");
    root.notice("notice msg....");
    root.warn("warn msg....");
    
    // 释放资源
    Category::shutdown();
}

void test2(){
    // 创建输出器对象
    FileAppender* appender2= new FileAppender("default","lot.txt");

    // 给输出器绑定格式化器对象
    PatternLayout* layout2=new PatternLayout{};
    //setConversionPattern(diy格式)
    layout2->setConversionPattern("%d [%p] %c -- %m%n");
    //绑定
    appender2->setLayout(layout2);

    // 获取根记录器
    Category &root=Category::getRoot();

    // 设置优先级
    root.setPriority(Priority::INFO);

    // 给记录器添加输出器
    root.addAppender(appender2);

    // 产生日志信息
    root.debug("debug msg....");
    root.info("info msg....");
    root.notice("notice msg....");
    root.warn("warn msg....");
    
    // 释放资源
    Category::shutdown();
}

void test3(){
    // 创建输出器对象 控制台
    OstreamAppender* appender1= new OstreamAppender("console",&cout);

    // 给输出器绑定格式化器对象
    PatternLayout* layout1=new PatternLayout{};
    //setConversionPattern(diy格式)
    layout1->setConversionPattern("%d [%p] %c : %m%n");
    //绑定
    
    appender1->setLayout(layout1);
    //创建输出器对象 文件
    FileAppender* appender2= new FileAppender("default","lot.txt");

    // 给输出器绑定格式化器对象
    PatternLayout* layout2=new PatternLayout{};
    //setConversionPattern(diy格式)
    layout2->setConversionPattern("%d [%p] %c -- %m%n");
    //绑定
    appender2->setLayout(layout2);

    // 获取根记录器
    Category &root=Category::getRoot();

    // 设置优先级
    root.setPriority(Priority::INFO);

    // 给记录器添加输出器
    root.addAppender(appender1);
    root.addAppender(appender2);

    // 产生日志信息
    root.debug("debug msg....");
    root.info("info msg....");
    root.notice("notice msg....");
    root.warn("warn msg....");
    
    // 释放资源
    Category::shutdown();
}

void test4(){
    // 创建输出器对象 控制台
    OstreamAppender* appender1= new OstreamAppender("console",&cout);

    // 给输出器绑定格式化器对象
    PatternLayout* layout1=new PatternLayout{};
    //setConversionPattern(diy格式)
    layout1->setConversionPattern("%d [%p] %c : %m%n");
    //绑定
    
    appender1->setLayout(layout1);
    //创建输出器对象 文件
    FileAppender* appender2= new FileAppender("default","lot.txt");

    // 给输出器绑定格式化器对象
    PatternLayout* layout2=new PatternLayout{};
    //setConversionPattern(diy格式)
    layout2->setConversionPattern("%d [%p] %c -- %m%n");
    //绑定
    appender2->setLayout(layout2);

    // 获取根记录器
    Category &root=Category::getRoot();

    // 设置优先级
    root.setPriority(Priority::INFO);

    //再获取子记录器
    Category& userModel=Category::getInstance("UserModel");

    // 给记录器添加输出器
    root.addAppender(appender1);
    // root.addAppender(appender2);

    // 产生日志信息
    root.debug("debug msg....");
    root.info("info msg....");
    root.notice("notice msg....");
    root.warn("warn msg....");
    // 产生日志信息
    userModel.debug("debug msg....");
    userModel.info("info msg....");
    userModel.notice("notice msg....");
    userModel.warn("warn msg....");
    
    // 释放资源
    Category::shutdown();
}

void test5(){
    // 创建输出器对象 控制台
    OstreamAppender* appender1= new OstreamAppender("console",&cout);

    // 给输出器绑定格式化器对象
    PatternLayout* layout1=new PatternLayout{};
    //setConversionPattern(diy格式)
    layout1->setConversionPattern("%d [%p] %c : %m%n");
    //绑定
    
    appender1->setLayout(layout1);
    //创建输出器对象 文件
    FileAppender* appender2= new FileAppender("default","lot.txt");

    // 给输出器绑定格式化器对象
    PatternLayout* layout2=new PatternLayout{};
    //setConversionPattern(diy格式)
    layout2->setConversionPattern("%d [%p] %c -- %m%n");
    //绑定
    appender2->setLayout(layout2);

    // 获取根记录器
    Category &root=Category::getRoot();

    // 设置优先级
    root.setPriority(Priority::INFO);

    // 给根记录器添加输出器
    root.addAppender(appender1);
    // root.addAppender(appender2);
    
    //再获取子记录器
    Category& userModel=Category::getInstance("UserModel");

    //给子记录器添加输出器
    userModel.addAppender(appender2);

    //如果不希望子记录器使用root的配置
    //setAdditivity(false)
    userModel.setAdditivity(false);

    // 产生日志信息
    root.debug("debug msg....");
    root.info("info msg....");
    root.notice("notice msg....");
    root.warn("warn msg....");
    // 产生日志信息
    userModel.debug("debug msg....");
    userModel.info("info msg....");
    userModel.notice("notice msg....");
    userModel.warn("warn msg....");
    
    // 释放资源
    Category::shutdown();
}

//测试回卷文件
void test6(){
    //
    RollingFileAppender* appender=
        new RollingFileAppender("roll","A.log",100,5);
    PatternLayout*layout=new PatternLayout();
    layout->setConversionPattern("%d [%p] %c %m%n");
    appender->setLayout(layout);

    Category &root=Category::getRoot();
    root.setPriority(Priority::INFO);
    root.addAppender(appender);

    for(int i=0;i<10;++i){
        //int ----> string
        std::string num=std::to_string(i);
        root.debug(num+"debug msg.");
        root.info(num+"info msg.");
        root.warn(num+"warn msg.");
    }
}

int main(int argc,char *argv[])
{
    // test1();
    // test2();
    // test3();
    // test4();
    // test5();
    test6();
    return 0;
}


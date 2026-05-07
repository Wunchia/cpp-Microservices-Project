#include <iostream>
#include <log4cpp/Category.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/LayoutAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using namespace log4cpp;
using std::string;

/*
 * 使用日志工具时，一般都会做封装处理
 * 对底层的log4cpp进行包装，套个外壳
 * 
 */

//自定义日志工具类
class MyLogger{
public:
    MyLogger()
    :m_category(Category::getRoot())
    {
        //构造函数体内完成初始化操作
        //给记录器配置一下
        OstreamAppender* appender=new OstreamAppender("console",&cout);
        PatternLayout* layout=new PatternLayout();
        layout->setConversionPattern("%d [%p] %c : %m%n");
        appender->setLayout(layout);

        m_category.setPriority(Priority::INFO);
        m_category.addAppender(appender);
    }

    void info(const string&msg){
        m_category.info(msg+"[file:"+__FILE__+"]"+"[function:"+__FUNCTION__+"]"+"[line:"+__LINE__+"]");
    }

    void debug(const string&msg){
        m_category.debug(msg);
    }

    void error(const string&msg){
        m_category.error(msg);
    }

private:
    //把记录器作为数据成员
    Category & m_category;
};

MyLogger logger;

void test1(){
    logger.error("数据库连接出错");
}

int main(int argc,char *argv[])
{
    logger.info("程序启动了");
    test1();    
    //获取文件名 行号 函数名
    cout<<__FUNCTION__<<endl;
    cout<<__FILE__<<endl;
    cout<<__LINE__<<endl;
    logger.info("程序结束了");
    return 0;
}


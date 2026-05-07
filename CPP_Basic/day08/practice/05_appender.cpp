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
using std::string;
using namespace log4cpp;

void test_three_appenders(){
    //OstreamAppender
    OstreamAppender* osApp=new OstreamAppender("console",&cout);
    PatternLayout* layout1=new PatternLayout{};
    layout1->setConversionPattern("%d [%p] %c: %m%n");
    osApp->setLayout(layout1);

    //FileAppender
    FileAppender* fileApp=new FileAppender("file","common.log");
    PatternLayout* layout2=new PatternLayout{};
    layout2->setConversionPattern("%d [%p] %c -- %m%n");
    fileApp->setLayout(layout2);

    //RollingFileAppender
    RollingFileAppender* rollApp=
        new RollingFileAppender("roll","rolling.log",1024*10,5);
    PatternLayout* layout3=new PatternLayout{};
    layout3->setConversionPattern("%d [%p] %c :: %m%n");
    rollApp->setLayout(layout3);

    Category &root=Category::getRoot();
    root.setPriority(Priority::DEBUG);

    root.addAppender(osApp);
    root.addAppender(fileApp);
    root.addAppender(rollApp);

    root.info("test 01 info");
    root.warn("Warning message");

    Category::shutdown();
}

int main(int argc,char *argv[])
{
    test_three_appenders();
    return 0;
}


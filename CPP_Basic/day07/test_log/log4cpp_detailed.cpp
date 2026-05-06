// 引入 log4cpp 的核心组件头文件
#include "log4cpp/Category.hh"       // 日志分类器，是操作日志的主入口
#include "log4cpp/Appender.hh"       // 日志输出目的地基类
#include "log4cpp/FileAppender.hh"   // 输出到文件的目的地
#include "log4cpp/OstreamAppender.hh"// 输出到标准输出流（如 std::cout）目的地
#include "log4cpp/Layout.hh"         // 日志布局基类
#include "log4cpp/BasicLayout.hh"    // 基础布局：格式为 "时间戳 优先级 分类名: 消息"
#include "log4cpp/Priority.hh"       // 日志优先级定义（DEBUG, INFO, WARN, ERROR 等）

int main(int argc, char** argv) {
    // 1. 创建第一个输出目的地：控制台输出
    // 参数1: 目的地名称；参数2: 指向 std::cout 的指针
    log4cpp::Appender *appender1 = new log4cpp::OstreamAppender("console", &std::cout);
    // 为该目的地设置布局。BasicLayout 是最简单的布局格式。
    appender1->setLayout(new log4cpp::BasicLayout());

    // 2. 创建第二个输出目的地：文件输出
    // 参数1: 目的地名称；参数2: 保存的日志文件名
    log4cpp::Appender *appender2 = new log4cpp::FileAppender("default", "program.log");
    // 同样为文件输出设置布局
    appender2->setLayout(new log4cpp::BasicLayout());

    // 3. 获取根分类器 (Root Category)
    // Category 是单例模式，通过 getRoot() 或 getInstance() 获取
    log4cpp::Category& root = log4cpp::Category::getRoot();
    // 设置根分类器的优先级。只有优先级大于等于 WARN 的日志才会被记录。
    // 优先级顺序：DEBUG < INFO < NOTICE < WARN < ERROR < CRIT < ALERT < EMERG
    root.setPriority(log4cpp::Priority::WARN);
    // 将控制台目的地绑定到根分类器
    root.addAppender(appender1);

    // 4. 获取/创建一个子分类器 "sub1"
    // sub1 默认继承 root 的优先级和 Appender（除非手动更改）
    log4cpp::Category& sub1 = log4cpp::Category::getInstance(std::string("sub1"));
    // 给 sub1 额外添加一个文件输出目的地。
    // 此时 sub1 的日志既会去 console（继承自root），也会去 program.log
    sub1.addAppender(appender2);

    // --- 使用方式 1：直接调用函数 ---
    // root 的优先级是 WARN。ERROR >= WARN，所以这行会打印。
    root.error("root error");
    // INFO < WARN，所以这行会被过滤掉，不会在控制台显示。
    root.info("root info");
    
    // sub1 也会受到优先级过滤（如果 sub1 没单独设优先级，则看 root）
    sub1.error("sub1 error");
    sub1.warn("sub1 warn");

    // --- 使用方式 2：Printf 风格 ---
    // 像 C 语言 printf 一样格式化输出变量
    root.warn("%d + %d == %s ?", 1, 1, "two");

    // --- 使用方式 3：C++ 流风格 (Stream) ---
    // 这种方式非常符合 C++ 习惯。通过操作符 << 拼接日志
    root << log4cpp::Priority::ERROR << "Streamed root error";
    // 同样，由于 INFO 优先级低于 WARN，下面这行不会有输出
    root << log4cpp::Priority::INFO << "Streamed root info";
    
    sub1 << log4cpp::Priority::ERROR << "Streamed sub1 error";
    sub1 << log4cpp::Priority::WARN << "Streamed sub1 warn";

    // --- 使用方式 4：便捷流函数 ---
    // errorStream() 会自动将优先级设为 ERROR
    root.errorStream() << "Another streamed error";

    // 注意：log4cpp 在程序结束时会自动释放单例和 Appender 资源，
    // 一般不需要手动 delete appender，Category 会负责管理。
    return 0;
}
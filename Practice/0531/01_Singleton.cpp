#include <iostream>

//饿汉式 程序启动时创建单例
// 如果构造依赖其他全局对象，初始化顺序可能出问题
class Singleton{
public:
    static Singleton& getInstance(){
        return instance;
    }
    Singleton(const Singleton&)=delete;
    Singleton& operator=(const Singleton&)=delete;
private:
    static Singleton instance;
    Singleton()=default;
    ~Singleton()=default;
};

Singleton Singleton::instance;

int main(int argc,char *argv[])
{
    Singleton& instance1=Singleton::getInstance();
    Singleton& instance2=Singleton::getInstance();
    std::cout<<&instance1<<std::endl<<&instance2<<std::endl;

    return 0;
}

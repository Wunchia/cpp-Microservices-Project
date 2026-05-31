#include <iostream>
using std::cout;
using std::endl;

//懒汉式 单例创建在堆区 线程不安全
class HeapSingleton{
public:
    static HeapSingleton* getInstance(){
        if(instance==nullptr){
            instance=new HeapSingleton();
        }
        return instance;
    }

    static void destroyInstance(){
        if(instance){
            delete instance;
            instance=nullptr;
        }
    }

    HeapSingleton(const HeapSingleton&)=delete;
    HeapSingleton& operator=(const HeapSingleton&)=delete;
private:
    HeapSingleton()=default;
    ~HeapSingleton()=default;
    static HeapSingleton* instance;
};

HeapSingleton* HeapSingleton::instance=nullptr;

int main(int argc,char *argv[])
{
    HeapSingleton* instance1=HeapSingleton::getInstance();
    HeapSingleton* instance2=HeapSingleton::getInstance();
    cout<<instance1<<endl<<instance2<<endl;
    HeapSingleton::destroyInstance();
    return 0;
}

#include <iostream>
#include <mutex>
#include <vector>
#include <thread>

using namespace std;

//std::call_once 保证传入的可调用对象在全进程范围内仅执行一次
// 且对所有线程可见。

class ThreadSafeHeapSingleton_V1{
public:
    static ThreadSafeHeapSingleton_V1*getInstance(){
        call_once(_onceFlag, init);
        return _instance;
    }

    static void destroyInstance(){
        if(_instance){
            delete _instance;
            _instance=nullptr;
        }
    }

    ThreadSafeHeapSingleton_V1(const ThreadSafeHeapSingleton_V1&)=delete;
    ThreadSafeHeapSingleton_V1&operator=(const ThreadSafeHeapSingleton_V1&)=delete;

private:
    ThreadSafeHeapSingleton_V1()=default;
    ~ThreadSafeHeapSingleton_V1()=default;
    static void init(){
        _instance=new ThreadSafeHeapSingleton_V1();
    }

    static ThreadSafeHeapSingleton_V1* _instance;
    static once_flag _onceFlag;//call_once的状态标记

    class Garbo{
    public:
        ~Garbo(){
            ThreadSafeHeapSingleton_V1::destroyInstance();
        }
    };
    static Garbo _garbo;
};

ThreadSafeHeapSingleton_V1* ThreadSafeHeapSingleton_V1::_instance=nullptr;
once_flag ThreadSafeHeapSingleton_V1::_onceFlag;
ThreadSafeHeapSingleton_V1::Garbo ThreadSafeHeapSingleton_V1::_garbo;

void test1(){
    ThreadSafeHeapSingleton_V1*p=ThreadSafeHeapSingleton_V1::getInstance();
    cout<<"V1:"<<p<<endl;
}

int main(int argc,char *argv[])
{
    const int N=10;
    vector<std::thread> threads;
    for(int i=0;i<N;++i){
        threads.emplace_back(test1);
    }
    for(auto&t:threads){t.join();}
    ThreadSafeHeapSingleton_V1::destroyInstance();
    return 0;
}

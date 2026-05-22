#include <iostream>
#include <mutex>
#include <atomic>
#include <thread>

class HeapSingleton{
public:
    HeapSingleton(const HeapSingleton&other)=delete;
    HeapSingleton& operator=(const HeapSingleton&other)=delete;
    HeapSingleton(HeapSingleton&&other)=delete;
    HeapSingleton& operator=(HeapSingleton&&other)=delete;

    /**
     * @brief 获取单例的全局访问点
     * @return 返回单例对象的原始指针
     */
    static HeapSingleton* getInstance(){
        HeapSingleton*tmp=_instance.load(std::memory_order_acquire);
        if(tmp==nullptr){
            std::lock_guard<std::mutex> lock(_mutex);
            tmp=_instance.load(std::memory_order_relaxed);
            if(tmp==nullptr){
                tmp=new HeapSingleton();
                _instance.store(tmp,std::memory_order_release);
            }
        }
        return tmp;
    }

    /**
     * @brief 手动释放接口
     */
    static void destroyInstance(){
        std::lock_guard<std::mutex> lock(_mutex);
        HeapSingleton*tmp=_instance.load(std::memory_order_relaxed);
        if(tmp!=nullptr){
            delete tmp;
            _instance.store(nullptr,std::memory_order_release);
            std::cout<<"destroyInstance()"<<std::endl;
        }
    }

private:
    HeapSingleton(){}
    ~HeapSingleton(){}
    static std::atomic<HeapSingleton*> _instance;//原子指针
    static std::mutex _mutex;//互斥锁

    class GarbageCollector{
    public:
        ~GarbageCollector(){
            HeapSingleton::destroyInstance();
            std::cout<<"GarbageCollector-->HeapSingleton::~HeapSingleton()"<<std::endl;
        }
    };
    static GarbageCollector _gc;
};

std::atomic<HeapSingleton*> HeapSingleton::_instance(nullptr);
std::mutex HeapSingleton::_mutex;
HeapSingleton::GarbageCollector HeapSingleton::_gc;

int main(int argc,char *argv[]){
    {
        HeapSingleton *hs1=HeapSingleton::getInstance();
        HeapSingleton *hs2=HeapSingleton::getInstance();
        std::cout<<"hs1="<<hs1<<" hs2="<<hs2<<std::endl;
        HeapSingleton::destroyInstance();
        std::cout<<"hs1="<<hs1<<" hs2="<<hs2<<std::endl;
        HeapSingleton *hs3=HeapSingleton::getInstance();
        std::cout<<"hs3="<<hs3<<std::endl;
    }
    return 0;
}

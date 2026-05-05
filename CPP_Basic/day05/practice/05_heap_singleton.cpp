#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class HeapSingleton{
public:
    static HeapSingleton* getInstance(){
        if(!ms_heapSingleton){
            ms_heapSingleton=new HeapSingleton();
        }
        return ms_heapSingleton;
    }

    static void destroy(){
        if(ms_heapSingleton){
            delete ms_heapSingleton;
            ms_heapSingleton=nullptr;
        }
    }
private:
    HeapSingleton(){}
    HeapSingleton& operator=(const HeapSingleton&)=delete;
    HeapSingleton(const HeapSingleton&)=delete;
    static HeapSingleton* ms_heapSingleton;
};

HeapSingleton* HeapSingleton::ms_heapSingleton=nullptr;

void test(){
    HeapSingleton* instance1=HeapSingleton::getInstance();
    HeapSingleton* instance2=HeapSingleton::getInstance();
    cout<<instance1<<" "<<instance2<<endl;
    HeapSingleton::destroy();
    instance1=nullptr;
    instance2=nullptr;
}

int main(int argc,char *argv[])
{
    test();    
    return 0;
}


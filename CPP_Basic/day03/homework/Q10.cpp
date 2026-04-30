#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;

class Demo{
    std::string name;
public:
    Demo(std::string n):name(n){
        cout<<"构造："<<name<<endl;
    }
    ~Demo(){
        cout<<"析构：" <<name<<endl;
    }
};

Demo globalObj("全局对象(Global)");

void testFunc(){
    cout<<"testFunc start"<<endl;
    Demo localObj("局部对象(Local)");

    static Demo StaticObj("静态对象(Static)");

    Demo* heapObj=new Demo("堆对象(Heap)");

    cout<<"------in testFunc-------"<<endl;
    delete heapObj;
    heapObj=nullptr;
    cout<<"testFunc end"<<endl;
}

int main(int argc,char *argv[])
{
    cout<<"main begin"<<endl;
    testFunc();
    cout<<"main end"<<endl;
    return 0;
}


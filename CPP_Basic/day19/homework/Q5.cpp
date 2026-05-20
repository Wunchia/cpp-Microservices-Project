#include <iostream>
#include <memory>
using std::unique_ptr;
using std::shared_ptr;
using std::weak_ptr;
using std::cin;
using std::cout;
using std::endl;

void test1(){
    int *raw_ptr=new int(100);

    // unique_ptr<int> up1(raw_ptr);
    // unique_ptr<int> up2(raw_ptr);//double free
    
    shared_ptr<int> sp1(raw_ptr);
    shared_ptr<int> sp2(raw_ptr);//double free
    cout<<"usesCount of sp1"<<sp1.use_count()<<endl;
    cout<<"usesCount of sp2"<<sp2.use_count()<<endl;//引用计数未能正确计算
}

void test2(){
    auto up=std::make_unique<int>(100);
    auto sp1=std::make_shared<int>(100);
    auto sp2=sp1;
    cout<<"useCount of sp1="<<sp1.use_count()<<endl;
}

// class Widget{
// public:
//     shared_ptr<Widget> getSelf(){
//         return shared_ptr<Widget>(this);//这里新造了一个计数器
//     }
// };//在test3中会double free

class Widget:public std::enable_shared_from_this<Widget>{
public:
    shared_ptr<Widget> getSelf(){
        return shared_from_this();//共享当前对象的shared_ptr
    }
};

void test3(){
    auto w1=std::make_shared<Widget>();
    auto w2=w1->getSelf();
    cout<<"w1 Count: "<<w1.use_count()<<endl;
    cout<<"w2 Count: "<<w2.use_count()<<endl;
}

void test4(){
    auto up=std::make_unique<int>(42);
    int *raw=up.get();
    delete raw;//double free
}

void test5(){
    auto up=std::make_unique<int>(42);
    int *raw=up.release();//up释放所有权 up变为空指针
    delete raw;
}

int main(int argc,char *argv[])
{
    // test1();
    // test2();
    // test3();
    test4();
    return 0;
}


#include <iostream>
#include <memory>
using std::cin;
using std::cout;
using std::endl;
using std::shared_ptr;
using std::weak_ptr;

/*
 * 循环引用问题
 * 1. shared_ptr的引用计数是通过一个控制块来实现的，
 * 控制块中包含了一个引用计数器和一个指向资源的指针。
 * 当两个shared_ptr对象互相引用对方时，就会形成循环引用，
 * 导致引用计数永远不会归零，从而导致内存泄漏。
 * 2. 解决循环引用问题的方法是使用weak_ptr，
 * weak_ptr是一种不拥有资源的智能指针，
 * 它不会增加引用计数器的值，因此不会导致循环引用问题。
 * 3. 在使用weak_ptr时，可以通过lock()方法获取一个shared_ptr对象，
 * 如果资源已经被释放，lock()方法会返回一个空的shared_ptr对象。
 * 4. 在设计类时，如果存在循环引用的情况，
 * 可以考虑使用weak_ptr来打破循环引用，以确保资源能够正确地释放。
 * 
 */
class Child;
class Parent{
public:
    // shared_ptr<Child> m_spChild;
    weak_ptr<Child> m_spChild;//不会使引用计数器增加
};

class Child{
public:
    // shared_ptr<Parent> m_spParent;
    weak_ptr<Parent> m_spParent;
};

void test1(){
    shared_ptr<Parent> parentPtr(new Parent{});
    shared_ptr<Child> childPtr(new Child{});
    //获取引用计数
    cout<<"parentPtr use_count()="<<parentPtr.use_count()<<endl;
    cout<<"childPtr use_count()="<<childPtr.use_count()<<endl;
    cout<<"-----------------------------"<<endl;
    //进行赋值
    parentPtr->m_spChild=childPtr;
    childPtr->m_spParent=parentPtr;
    cout<<"parentPtr use_count()="<<parentPtr.use_count()<<endl;
    cout<<"childPtr use_count()="<<childPtr.use_count()<<endl;
}

int main(int argc,char *argv[])
{
    test1(); 
    return 0;
}


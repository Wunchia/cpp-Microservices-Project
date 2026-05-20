#include <iostream>
#include <memory>
#include <string>
using std::string;
using std::shared_ptr;
using std::unique_ptr;
using std::weak_ptr;
using std::cin;
using std::cout;
using std::endl;

class Resource{
public:
    Resource(){cout<<"Resource()"<<endl;}
    ~Resource(){cout<<"~Resource()"<<endl;}
    void doSomething(){cout<<"do something"<<endl;}
};

struct Node{
    string name;
    shared_ptr<Node> sharedNext;
    weak_ptr<Node> weakNext;

    Node(string n)
    : name(n) 
    {
        cout<<"Node("<<name<<")"<<endl;
    }

    ~Node(){
        cout<<"~Node("<<name<<")"<<endl;
    }
};

void test1(){
    cout<<"===unique_ptr 独占与所有权转移==="<<endl;
{
    unique_ptr<Resource> ptr1=std::make_unique<Resource>();

    unique_ptr<Resource> ptr2=std::move(ptr1);
    if(!ptr1){
        cout<<"ptr1 is empty"<<endl;
    }
    if(ptr2){
        ptr2->doSomething();
    }
}
    cout<<"-----离开作用域，资源被释放-----"<<endl;
}

void test2(){
    cout<<"===shared_ptr 共享所有权==="<<endl;
{
    shared_ptr<Resource> ptr1=std::make_shared<Resource>();

    shared_ptr<Resource> ptr2=ptr1;
    cout<<"ptr1 use_count: "<<ptr1.use_count()<<endl;
    cout<<"ptr2 use_count: "<<ptr2.use_count()<<endl;

    if(ptr1){
        ptr1->doSomething();
    }
    
}
    cout<<"-----离开作用域，资源被释放-----"<<endl;
}

void test3(){
    cout<<"===weak_ptr 观察者，不拥有资源==="<<endl;
{
    shared_ptr<Node> node1=std::make_shared<Node>("Node1");
    shared_ptr<Node> node2=std::make_shared<Node>("Node2");

    // node1->sharedNext=node2;
    // node2->sharedNext=node1;

    node1->weakNext=node2;
    node2->weakNext=node1;

    cout<<"node1 use_count: "<<node1.use_count()<<endl;
    cout<<"node2 use_count: "<<node2.use_count()<<endl;
}
    cout<<"-----离开作用域，资源被释放-----"<<endl;
}

void test4(){
    cout<<"===shared_ptr & weak_ptr 计数与解密==="<<endl;
    shared_ptr<Resource> sPtr1=std::make_shared<Resource>();
    cout<<"sPtr1 use_count: "<<sPtr1.use_count()<<endl;
{
    shared_ptr<Resource> sPtr2=sPtr1;//共享所有权
    cout<<"sPtr1 use_count: "<<sPtr1.use_count()<<endl;

    weak_ptr<Resource> wPtr=sPtr1;//观察者，不增加引用计数
    cout<<"sPtr1 use_count: "<<sPtr1.use_count()<<endl;

    if(auto lockedPtr=wPtr.lock()){
        cout<<"使用lockedPtr访问资源"<<endl;
        lockedPtr->doSomething();
    }
}
    cout<<"sPtr1 use_count: "<<sPtr1.use_count()<<endl;
    cout<<"-----离开作用域，资源被释放-----"<<endl;
}

void test5(){
    cout<<"===循环引用问题与解决==="<<endl;
    auto nodeA=std::make_shared<Node>("NodeA");
    auto nodeB=std::make_shared<Node>("NodeB");

    nodeA->sharedNext=nodeB;
    nodeB->weakNext=nodeA;
    // nodeB->sharedNext=nodeA;

    cout<<"NodeA count"<<nodeA.use_count()<<endl;
    cout<<"NodeB count"<<nodeB.use_count()<<endl;
}

int main(int argc,char *argv[])
{
    // test1();
    // test2();
    // test3();
    // test4();
    test5();
    return 0;
}


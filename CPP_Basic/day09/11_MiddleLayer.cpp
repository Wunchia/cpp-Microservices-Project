#include <iostream>
#include <memory>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::auto_ptr;

/*
 * 成员访问运算符： ->  *
 * operator->
 *
 * operator*
 * 
 * Type * p = new Type();
 * p->m_data;
 * p->func();
 * 
 * (*p).m_data;
 * (*p).func();
 * 
 * 一般情况下通过指针来做的操作，
 * 重载后可以像使用指针一样去使用对象
 * 
 * 自动资源释放：利用栈对象的生命周期进行自动资源释放
 */


class Data{
public:
    Data(){
        cout<<"Data()"<<endl;
    }

    int getData(){
        return m_data;
    }

    ~Data(){
        cout<<"~Data()"<<endl;
    }
private:
    int m_data=1;
};

class MiddleLayer{
public:
    MiddleLayer(Data*p)
    :m_p(p)//浅拷贝
    {
        cout<<"MiddleLayer(Data *)"<<endl;
    }

    ~MiddleLayer(){
        cout<<"~MiddleLayer()"<<endl;
        if(m_p){
            delete m_p;
            m_p=nullptr;
        }
    }

    // operator->
    //返回值必须是指针或者重载了->运算符的对象
    Data* operator->(){
        return m_p;
    }

    // operator*
    Data& operator*(){
        return *m_p;
    }

private:
    //原生指针 or 原始指针 or 裸指针 or 底层指针
    Data *m_p;
};

void test1(){
    // 栈对象
    Data data;
    //对象.成员访问
    data.getData();

    // 堆对象
    Data * p=new Data{};
    //指针->成员访问
    p->getData();
    //(*指针).成员访问
    (*p).getData();

    //手动释放资源
    delete p;
    p=nullptr;
}

void test2(){
    Data * p=new Data{};
    // 创建栈对象
    MiddleLayer ml{p};

    //delete p; 自动资源管理 不再需要手动释放 这么写反而会double free
}

void test3(){
    // 把堆上的Data对象当作一个内存资源
    // 把该资源交给了 ml 这个管理者对象来负责回收内存资源
    MiddleLayer ml{new Data{}};//不向外暴露 p 防止double free
    // ml对象就在扮演智能指针的角色

    //希望通过ml对象访问所管理的资源 getData()
    //getData()的调用：Data对象.getData()  Data*->getData()
    
    cout<<(*ml).getData()<<endl;
    //ml.operator*()  -->  Data对象.getData(); 
    //本质：
    ml.operator*().getData();

    cout<<"------------------------"<<endl;

    cout<<ml->getData()<<endl;
    //ml.operator->()  -->  Data*->getData();
    //本质：
    ml.operator->()->getData();
}

//智能指针
void test4(){
    //通过智能指针进行资源管理
    auto_ptr<Data> ap{new Data{}};
    cout<<ap->getData()<<endl;
    cout<<(*ap).getData()<<endl;
}

int main(int argc,char *argv[])
{
    test3();
    // test4();
    return 0;
}


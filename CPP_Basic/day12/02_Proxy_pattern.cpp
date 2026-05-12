#include <iostream>
using std::cin;
using std::cout;
using std::endl;

/*
 * 代理设计模式：委托类 代理类--> 帮委托做事情
 *
 * 景天类：委托--->买包子
 *
 * 空灵类：代理
 * 
 * 常见的代理实现方式：
 * 1.将委托作为代理类中的数据成员
 * 2.将委托作为代理类的父类 使用继承
 */

//委托类
class JingTian{
public:
    void buyBreakfast(){
        cout<<"买2个包子"<<endl;
    }

private:
};

//代理类
class KongLing{
public:
    KongLing(JingTian jingtian)
    :m_jingtian(jingtian)
    {}

    void buyBreakfast(){
        m_jingtian.buyBreakfast();
    }
    JingTian& m_jingtian;
};

void test1(){
    JingTian jingtian;
    KongLing kongling{jingtian};
    kongling.buyBreakfast();
}



//委托类
class JingTian2{
public:
    void buyBreakfast(){
        cout<<"买2个包子"<<endl;
    }

private:
};

//代理类
//将景天设置为空灵的父类
class KongLing2:public JingTian2
{
public:
    void buyBreakfast(){
        cout<<"帮景天"<<endl;
        JingTian2::buyBreakfast();
    }
};

void test2(){
    KongLing2 kl;
    kl.buyBreakfast();
}

int main(int argc,char *argv[])
{
    // test1();
    test2();
    return 0;
}


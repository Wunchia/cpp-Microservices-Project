#include <iostream>
using std::cin;
using std::cout;
using std::endl;

/*
 * const成员函数：在成员函数的形参列表后 加const
 * 
 * 语法：
 * 返回值类型 函数名（形参列表）const{}
 * 特点：
 * const和成员函数结合，具有只读属性，不能修改对象状态
 * 即成员函数的取值不能改
 * 
 */
class A{
public:
    int num=1;
};

class Point{
public:
    Point(int x,int y){}

    //const成员函数
    void show()const{
        //const成员函数中的this指针是双重const限定的指针
        //不能改指向 也不能改内容
        this;
        //this->m_x=1;
        m_x;
        m_y; 
        //const其实直接跟在了this指针前，所以对象内容不能改
        //m_x=1;
        //m_y=2;
        m_a.num;
        //m_a.num=10;
    }

    void show(){}//函数重载 
        //隐含参数this未被const修饰，类型不同，构成函数重载
        //两个版本中的函数中隐含的this类型不一样

    //什么时候使用const函数？ 只让访问 不让修改 的时候
    int getX()const{
        //m_x=10;//报错 禁止修改行为
        return m_x;
    }
private:
    int m_x;
    int m_y;
    A m_a;
};

void test1(){
    Point pt(1,2);
    int o_x=pt.getX();
    cout<<o_x<<endl;
}

int main(int argc,char *argv[])
{
    test1();    
    return 0;
}


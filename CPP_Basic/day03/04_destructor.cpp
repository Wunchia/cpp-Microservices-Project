#include <iostream>
#include <string.h>
using std::cin;
using std::cout;
using std::endl;

/*
 * 析构函数destructor：特殊的成员函数
 * 作用：对象销毁时会自动调用该函数
 *
 * 语法：
 *  ~类名（形参列表为空）{
 *      析构函数体
 *      释放资源的操作
 * }
 *
 * 资源：
 * 内存资源
 * 网络资源（端口号）
 * 文件资源（文件描述符）
 * 数据库链接
 * 线程
 * 
 * 析构函数的调用时机：(生命周期)
 * 1.局部对象
 * 2.全局对象
 * 3.静态对象
 * 4.堆上对象
 */

class Computer
{
public:
    Computer(const char *brand, int price)
        : m_brand(new char[strlen(brand) + 1]{}), m_price(price)
    {
        cout << "constructor" << endl;
        strcpy(m_brand, brand);
    }

    void print()
    {
        cout << m_brand << " " << m_price << endl;
    }
    // 如果不写析构函数 需要定义函数手动释放并在main中调用
    //  void release(){
    //      if(m_brand){
    //          delete[] m_brand;
    //          m_brand=nullptr;
    //      }
    //  }

    // destructor
    ~Computer()
    {
        cout << "~Computer()" << endl;
        if (m_brand)
        {
            delete[] m_brand;
            m_brand = nullptr;
        }
    }

private:
    char *m_brand;
    int m_price;
};

void test1()
{
    //局部对象：函数执行结束 栈帧销毁时调用析构函数
    Computer pc{"xiaomi", 1999};
    pc.print();
    // pc.release();
    // pc.~Computer();//手动调用析构函数，可以但不建议这么写
                      //一般上让析构函数自动去执行
}

//全局对象 在程序运行结束时触发析构函数
// Computer pc{"apple",9999};

void test2(){
    cout<<"test2 start"<<endl;
    //静态对象 在程序运行结束时触发析构函数
    static Computer pc{"apple",9999};
    cout<<"test2 end"<<endl;
}

void test3(){
    cout<<"test3 start"<<endl;
    //注意！！！堆上对象 不做操作不会释放
    // int *p=new int{1};
    Computer *p=new Computer{"xiaomi",1999};

    p->print();
    //delete指针时会调用析构函数
    delete p;
    p=nullptr;
    cout<<"test3 end"<<endl;
}


int main(int argc, char *argv[])
{
    cout<<"main start"<<endl;
    // test1();
    // test2();
    test3();
    cout<<"main end"<<endl;
    return 0;
}

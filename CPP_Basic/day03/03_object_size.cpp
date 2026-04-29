#include <iostream>
using std::cin;
using std::cout;
using std::endl;

/*
 * 一个对象的大小和类中数据成员有关
 * 取决于数据成员的类型  
 * 
 *  特殊情况：
 *  内存对齐 一般按 8 字节 对齐
 *  会按照类中最大的那个数据成员的整数倍来对齐
 * 
 *  还和声明的数据成员的顺序有关
 * 
 *  如果类中有数组作为数据成员
 *  会按照除了数组外最大的数据成员的整数倍对齐 
 *  
 *  空对象大小为 1 字节
 */

class Point{
public:
    //无参构造函数
    Point(){
        cout<<"Point()"<<endl;
    }

    //有参构造函数
    Point(int x,int y)
    :m_x(x),m_y(m_x)
    {
        cout<<"Point(int,int)"<<endl;
    }

    void print(){
        cout<<m_x<<" "<<m_y<<endl;
    }
private:
    //列表初始化的顺序 依照类内成员变量声明的顺序
    // int m_y;
    // int m_x;

    int m_y;
    double m_x;
};

void test01(){
    Point pt;
    cout<<sizeof(pt)<<endl;//int ---> 8
                           //double ---> 16
}

class C{
    int m_c1;
    int m_c2;
    double m_c3;
};

class D{
    int m_d1;
    double m_d2;
    int m_d3;
};

void test2(){
    cout<<"C:"<<sizeof(C)<<endl;
    cout<<"D:"<<sizeof(D)<<endl;
}

class E{
    double m_e;// 8
    char m_eArr[20];//凑至24 （8的整数倍）
    double m_e1;//8
    int m_e2;// 4+4=8
};

class F{
    char m_fArr[20];
};

class G{

};

void test3(){
    cout<<"E:"<<sizeof(E)<<endl;
    cout<<"F:"<<sizeof(F)<<endl;
    cout<<"G:"<<sizeof(G)<<endl;//空对象大小为 1 字节
}

int main(int argc,char *argv[])
{
    // test01();
    // test2();
    test3();
    return 0;
}


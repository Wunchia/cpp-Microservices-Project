#include <iostream>
using std::cin;
using std::cout;
using std::endl;

/*
 * 如果类中有const 版本和非const 版本的成员函数：
 * 1.普通对象-->非const版本的成员函数
 * 2.const对象-->const版本的成员函数
 * 
 * 如果类中只有非const版本的成员函数：
 * 1.普通对象-->可以调用非const版本的成员函数
 * 2.const对象-->error因为this类型不一样
 * 
 * 如果类中只有const版本的成员函数：
 * 1.普通对象-->都可以调用
 * 2.const对象-->都可以调用
 * 
 */

class Point{
public:
    Point(int x,int y)
    :m_x(x)
    ,m_y(y)
    {
        cout<<"Point(int,int)"<<endl;
    }

    Point(const Point&rhs)
    :m_x(rhs.m_x)
    ,m_y(rhs.m_y)
    {
        cout<<"Point(const Point&)"<<endl;
    }

    //const成员函数
    void show()const{
        cout<<"show()const"<<endl;
    }
    void show(){
        cout<<"show()"<<endl;
    }//函数重载 
    void print()const{
        cout<<m_x<<" "<<m_y<<endl;
    }
//private:
    int m_x;
    int m_y;
};

void test1(){
    Point pt1(1,2);
    pt1.show();
    //默认调用非const版本
    //如果只有const版本 就调const版本

    const Point pt2(3,4);//实例化的对象为常量 不可改
    pt2.show();
    //默认调用const版本
    //如果没有const版本会报错
}

//对象数组
//构建对象类型的数组的形式：
//1.可以通过左值对象构建数组
//2.可以通过右值对象构建数组
//3.通过初始化列表简写构建数组
void test2(){
    //int arr[3]={1,2,3};
    Point pt1{1,1};
    Point pt2{2,2};
    Point pt3{3,3};
    //将pt1 pt2 pt3作为数组元素时会调用拷贝构造
    //对象作为数组元素时 会调用拷贝构造
    //数组中存放的不是原本的对象 而是复制了一份
    Point pts[3]={pt1,pt2,pt3};
    pts[0].m_x=10;
    pts[0].print();
}

//右值对象构建数组
void test3(){
    Point pts[]={
        Point{1,1},
        Point{2,2},
        Point{3,3}
    };
    pts[0].print();
}

void test4(){
    //使用初始化列表进行简写
    Point pts[]={
        {1,1},
        {2,2},
        {3,3}
    };
    pts[0].print();
    cout<<"-------->"<<endl;
    for(int i=0;i<3;++i){
        pts[i].print();
    }
    cout<<"------->"<<endl;
    //foreach遍历 增强for循环（迭代循环）
    //会调用拷贝构造
    for(Point pt:pts){
        pt.print();
    }
    cout<<"-------->"<<endl;
    //使用关键字auto进行类型的自动推导
    for(const auto &pt:pts){
        pt.print();
    }
}

void test5(){
    //栈对象
    Point pt1{1,1};
    //对象.成员
    pt1.print();

    Point *p=&pt1;
    //指针->成员
    p->print();

    //堆对象
    //new int{1}
    //new int[]{1}
    Point *p2=new Point{1,2};
    p2->print();
    delete p2;
    p2=nullptr;

}

int main(int argc,char *argv[])
{
    //test1();    
    // test2();
    // test3();
    test4();
    // test5();
    return 0;
}


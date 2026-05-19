#include <iostream>
#include <memory>
using std::cin;
using std::cout;
using std::endl;
using std::auto_ptr;

/*
 * 智能指针：
 * auto_ptr:仅作了解，后续C++版本已弃用
 * unique_ptr:独占所有权
 * shared_ptr:共享所有权
 * weak_ptr:
 * 
 */

class Point{
public:
    Point(int x,int y)
    :m_x(x)
    ,m_y(y)
    {}

    void print(){
        cout<<m_x<<" "<<m_y<<endl;
    }

private:
    int m_x;
    int m_y;
};

//auto_ptr 的使用
void test1(){
    auto_ptr<Point> ap{new Point{1,2}};
    ap->print();
    (*ap).print();
    ap.get()->print();
}

void test2(){
    auto_ptr<Point> ap{new Point{3,4}};
    ap->print();
    cout<<"---------------"<<endl;
    auto_ptr<Point>ap2=ap;
    ap2->print();
    cout<<"--------------"<<endl;
   // ap->print(); //段错误 资源已经被转移给其他智能指针了
}

int main(int argc,char *argv[])
{
    // test1(); 
    test2();
    return 0;
}


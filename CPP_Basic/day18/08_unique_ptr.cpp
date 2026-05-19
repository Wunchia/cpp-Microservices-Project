#include <iostream>
#include <memory>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::unique_ptr;
using std::vector;

/*
 * unique_ptr智能指针：独占资源所有权
 * 不允许复制相关的操作：拷贝构造和赋值运算符都删除了
 * 注意：
 * unique_ptr作为容器中的元素
 * 
 */

class Point{
public:
    Point(int x,int y)
    :m_x(x)
    ,m_y(y)
    {}

    ~Point(){
        cout<<"~Point()"<<endl;
    }

    void print(){
        cout<<m_x<<" "<<m_y<<endl;
    }

private:
    int m_x;
    int m_y;
}; 

void test1(){
    //把资源交给智能指针来管理
    //利用构造函数创建的智能指针对象
    unique_ptr<Point> up{new Point{1,2}};
    up->print();
    (*up).print();
    up.get()->print();
}

//测试 独占所有权
void test2(){
    unique_ptr<Point> up{new Point{1,2}};
    //测试拷贝构造 已经被delete 删除了 不允许复制
    // unique_ptr<Point> up2=up;

    unique_ptr<Point> up3{new Point{3,4}};
    //测试赋值 不允许赋值操作
    // up3=up;
}

//测试 unique_ptr 作为容器的元素
void test3(){
    vector<unique_ptr<Point>> v;
    unique_ptr<Point> up1{new Point{1,1}};
    unique_ptr<Point> up2{new Point{2,2}};
    unique_ptr<Point> up3{new Point{3,3}};
    //把元素放入到vector中
    //v.push_back(up1);//会报错 因为传参会调用拷贝构造 但这里已经被删除了
    v.push_back(std::move(up1));
    v.push_back(std::move(up2));
    v.push_back(std::move(up3));
    v[0]->print();
    cout<<"-------------"<<endl;
    //原来的up1\up2\up3就不能用了
    //up1->print();//这里因为使用了移动拷贝 up1已经不管理Point了
    //段错误
}

void test4(){
    //up1管理的资源是个Point{1,1}
    unique_ptr<Point> up1{new Point{1,2}};
    up1->print();
    //reset()替换被管理的对象
    up1.reset(new Point{3,4});
    up1->print();
}

int main(int argc,char *argv[])
{
    // test3();    
    test4();
    return 0;
}


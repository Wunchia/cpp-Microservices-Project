#include <iostream>
#include <memory>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::shared_ptr;
using std::vector;

/*
 * shared_ptr:共享所有权的智能指针
 * 可以进行赋值、复制操作--->进行共享所有权
 */

class Point{
public:
    Point(int x,int y)
        :_x(x)
        ,_y(y)
    {
        cout<<"Point(int,int)"<<endl;
    }
    ~Point(){
        cout<<"~Point()"<<endl;
    }
    void print()const{
        cout<<"("<<_x<<","<<_y<<")"<<endl;
    }
private:
    int _x;
    int _y;
};

//创建shared_ptr对象 并测试共享所有权
void test1(){
    shared_ptr<Point> sp1(new Point(1,2));
    auto sp2 = std::make_shared<Point>(3,4);
    sp1->print();
    sp2->print();
    cout<<"sp1 use_count()="<<sp1.use_count()<<endl;

    //shared_ptr<Point> sp2=sp1;//复制构造函数
    shared_ptr<Point> sp3(sp1);//复制构造函数
    sp3->print();
    cout<<"sp3 use_count()="<<sp3.use_count()<<endl;
    cout<<"----------------"<<endl;
    shared_ptr<Point> sp4{new Point(5,6)};//直接初始化
    cout<<"sp4 use_count()="<<sp4.use_count()<<endl;
    cout<<"----------------"<<endl;
    sp4=sp1;//赋值操作
    sp4->print();
    cout<<"sp1 use_count()="<<sp1.use_count()<<endl;
    cout<<"sp2 use_count()="<<sp2.use_count()<<endl;
    cout<<"sp3 use_count()="<<sp3.use_count()<<endl;
    cout<<"sp4 use_count()="<<sp4.use_count()<<endl;
}

//非法的共享 ----> double free
void test2(){
    //原始指针暴露出来
    Point* p=new Point(1,2);
    shared_ptr<Point> sp1(p);
    sp1->print();
    cout<<"---------"<<endl;
    shared_ptr<Point> sp2(p);//非法的共享
    sp2->print();
    sp1->print();
    cout<<"sp1 use_count()="<<sp1.use_count()<<endl;
    cout<<"sp2 use_count()="<<sp2.use_count()<<endl;
}

//其他形式的非法共享
void test3(){
    shared_ptr<Point> sp1{new Point(1,2)};
    shared_ptr<Point> sp2(sp1.get());//非法的共享
    sp1->print();
    sp2->print();
    cout<<"sp1 use_count()="<<sp1.use_count()<<endl;
    cout<<"sp2 use_count()="<<sp2.use_count()<<endl;
}

void test4(){
    vector<shared_ptr<Point>> v;
    shared_ptr<Point> sp1{new Point(1,2)};
    shared_ptr<Point> sp2{new Point(3,4)};
    shared_ptr<Point> sp3{new Point(5,6)};
    v.push_back(sp1);
    v.push_back(sp2);
    v.push_back(sp3);
    v[0]->print();
    v[1]->print();
}

int main(int argc,char *argv[])
{
    // test1();
    // test2();
    // test3();
    test4();
    return 0;
}


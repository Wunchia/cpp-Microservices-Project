#include <iostream>
#include <memory>
using std::cin;
using std::cout;
using std::endl;
using namespace std;
/*
 * 智能指针的误用：一般情况下形式可能不同，
 * 但本质是类似的，都是原始指针交给不同的智能指针对象进行管理
 */

class Point : public enable_shared_from_this<Point>
{
public:
    Point(int x=0,int y=0)
    :_x(x)
    ,_y(y)
    {
        cout<<"Point(int ,int)"<<endl;
    }

    ~Point(){
        cout<<"~Point()"<<endl;
    }

    shared_ptr<Point> addPoint(Point *pt){
        _x+=pt->_x;
        _y+=pt->_y;
        return shared_from_this();
    }

    void print(){
        cout<<_x<<" "<<_y<<endl;
    }

private:
    int _x;
    int _y;
};

void test1(){
    unique_ptr<Point> up1{new Point{1,2}};
    unique_ptr<Point> up2{up1.get()};
    up1->print();
    up2->print();
}

void test2(){
    shared_ptr<Point> sp1{new Point{1,2}};
    shared_ptr<Point> sp2{sp1.get()};
    sp1->print();
    sp2->print();
}

void test3(){
    Point * p=new Point{1,2};
    unique_ptr<Point> up1{p};
    unique_ptr<Point> up2{p};
    up1->print();
    up2->print();
}

void test4(){
    Point * p=new Point{1,2};
    shared_ptr<Point> sp1{p};
    shared_ptr<Point> sp2{p};
    sp1->print();
    sp2->print();
}

void test5(){
    shared_ptr<Point> sp1(new Point{1,2});
    shared_ptr<Point> sp2(new Point{3,4});

    shared_ptr<Point> sp3(sp1->addPoint(sp2.get()));
    cout<<"sp3=";
    sp3->print();
    
    cout<<"sp1.count: "<<sp1.use_count()<<endl;
    cout<<"sp3.count: "<<sp3.use_count()<<endl;
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


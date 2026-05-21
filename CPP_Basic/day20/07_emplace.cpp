#include <iostream>
#include <vector>
#include <list>
#include <deque>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

class Point{
public:
    //构造函数
    Point(int x=0,int y=0):_x(x),_y(y){
        cout<<"Point(int,int)"<<endl;
    }
    //拷贝构造函数
    Point(const Point &pt):_x(pt._x),_y(pt._y){
        cout<<"Point(const Point &)"<<endl;
    }
    //移动构造函数
    Point(Point &&pt):_x(pt._x),_y(pt._y){
        cout<<"Point(Point &&)"<<endl;
    }
    //析构函数
    ~Point(){
        cout<<"~Point()"<<endl;
    }
    //打印函数
    void print(){
        cout<<_x<<" "<<_y<<endl;
    }

private:
    int _x;
    int _y;
};

void test1(){
    list<Point> box;
    // Point pt(1,2);
    //push_back 会调用拷贝构造函数
    {
        box.push_back(Point{1,2});
    }
    cout<<"---------->"<<endl;
    //emplace_back 会调用构造函数
    {
        box.emplace_back(3,4);
    }
    cout<<"---------->"<<endl;
    // Point pt2(5,6);
    auto it=box.begin();
    {
        it=box.insert(it,Point{5,6});//会调用拷贝构造函数
    }
    cout<<"---------->"<<endl;
    {
        it=box.emplace(it,7,8);//会调用构造函数
    }
    cout<<"---------->"<<endl;
}

int main(int argc,char *argv[])
{
    test1();
    return 0;
}


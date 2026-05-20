#include <iostream>
#include <memory>
using std::cin;
using std::cout;
using std::endl;
using std::shared_ptr;
using std::weak_ptr;

/*
 * weak_ptr的使用
 * 
 */

class Point{
public:
    Point(int x,int y):_x(x),_y(y){}
    void print(){
        cout<<"("<<_x<<","<<_y<<")"<<endl;
    }
private:
    int _x;
    int _y;
};

void test1(){
    shared_ptr<Point> sp(new Point(1,2));
    // weak_ptr的创建 接收一个shared_ptr对象作为参数
    // 一般配合shared_ptr使用，作为shared_ptr的伴侣指针
    weak_ptr<Point> wp(sp);

    cout<<"sp use_count()="<<sp.use_count()<<endl;
    cout<<"wp use_count()="<<wp.use_count()<<endl;
    cout<<"-----------------------------"<<endl;
    //不能直接通过weak_ptr访问资源
    //wp->print(); //编译错误

    //只能把weak_ptr转换成shared_ptr才能访问资源
    //使用lock()方法转换成shared_ptr对象
    weak_ptr<Point> wp2;
    //if(wp.lock()){
    if(auto sp2=wp.lock()){
        cout<<"转换成功"<<endl;
        sp2->print();
    }else{
        cout<<"转换失败"<<endl;
    }
    cout<<"-----------------------------"<<endl;
    sp.reset();//释放资源
    cout<<wp.expired()<<endl;//判断资源是否已经被释放    
}

int main(int argc,char *argv[])
{
    test1(); 
    return 0;
}


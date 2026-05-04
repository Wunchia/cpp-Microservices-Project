#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class Point{
public:
    Point(int x,int y)
    :m_x(x)
    ,m_y(y)
    {
        cout<<"Point(int,int)"<<endl;
    }
public:
    Point(const Point&rhs)
    :m_x(rhs.m_x)
    ,m_y(rhs.m_y)
    {
        cout<<"Point(const Point&)"<<endl;
    }
// private:
    ~Point(){
        cout<<"~Point()"<<endl;
    }
public:
    void print()const{
        cout<<m_x<<" "<<m_y<<endl;
    }
// private:
    //new 和 delete 的底层依然用的是malloc和free
    //operator new
    void* operator new(size_t size){
        cout<<"operator new"<<endl;
        //底层使用malloc
        return malloc(size);
    }

    //operator delete
    void operator delete(void *p){
        cout<<"operator delete"<<endl;
        free(p);
    }
//private:
    int m_x;
    int m_y;
};

void test1(){
    Point *p=new Point{1,2};
    delete p;
}

//创建栈对象需要什么条件？
//public权限的构造函数；
//public权限的析构函数
//和operator new/delete 没有关系
void test2(){
    Point pt{1,2};
    //需要调用构造函数、析构函数
}

//创建堆对象需要什么条件？
//public权限的构造函数；
//public权限的operator new/delete
//单纯创建堆对象和析构函数没关系
void test3(){
    Point*p=new Point{1,2};//不涉及析构
    //执行 delete p 的时候才需要析构
}

//只允许创建堆对象
//将析构函数设为private

//只允许创建栈对象
//将 operator new/delete 设为private

int main(int argc,char *argv[])
{
    // test1();
    // test2();
    test3();
    return 0;
}


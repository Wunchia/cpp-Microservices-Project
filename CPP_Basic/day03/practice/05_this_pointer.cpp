#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class Point{
public:
    Point(int x,int y):x(x),y(y){}

    void checkThis(){
        cout<<"当前对象地址："<<this<<endl;
    }

private:
    int x,y;
};


void test(){
    Point p1{1,2};
    cout<<"p1地址"<<&p1<<endl;
    p1.checkThis();
}


int main(int argc,char *argv[])
{
    test(); 
    return 0;
}


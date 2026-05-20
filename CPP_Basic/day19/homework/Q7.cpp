#include <iostream>
#include <memory>
#include <vector>
using std::unique_ptr;
using std::vector;
using std::cin;
using std::cout;
using std::endl;

class Point{
public:
    Point(int x=0,int y=0)
    :_x(x)
    ,_y(y)
    {
        cout<<"Point(int,int)"<<endl;
    }

    ~Point(){
        cout<<"~Point()"<<endl;
    }

    void print(){
        cout<<"("<<_x<<","<<_y<<")"<<endl;
    }

private:
    int _x;
    int _y;
};


void test(){
    vector<unique_ptr<Point>> pv;
    pv.push_back(std::move(std::make_unique<Point>(1,2)));
    pv.push_back(std::move(std::make_unique<Point>(3,4)));
    pv.push_back(std::move(std::make_unique<Point>(5,6)));

    for(const auto &p:pv){
        if(p){
            p->print();
        }
    }
}

int main(int argc,char *argv[])
{
    test();    
    return 0;
}


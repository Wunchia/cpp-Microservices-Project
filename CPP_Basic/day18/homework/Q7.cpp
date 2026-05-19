#include <iostream>
#include <vector>
#include <memory>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::unique_ptr;

class Point{
public:
    Point(int x=0,int y=0)
    :_x(x)
    ,_y(y)
    {}

    void display()const{
        cout<<"["<<_x<<" , "<<_y<<"]"<<endl;
    }

private:
    int _x;
    int _y;
};

void test(){
    vector<unique_ptr<Point>> pv;

    pv.push_back(std::make_unique<Point>(1,2));
    pv.push_back(std::make_unique<Point>(3,4));

    auto p=std::make_unique<Point>(5,6);
    pv.push_back(std::move(p));

    for(const auto& ptr:pv){
        if(ptr){
            ptr->display();
            // (*ptr).display();
            // ptr.get()->display();
        }
    }
}

int main(int argc,char *argv[])
{
    test();
    return 0;
}


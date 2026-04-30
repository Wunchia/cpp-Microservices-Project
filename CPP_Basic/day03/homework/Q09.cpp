#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class Rectangle{
private:
    double length;
    double width;
public:
    Rectangle(double l,double w):length(l),width(w){}
    double calcPerimeter(){
        return 2*(length+width);
    }
    double calcArea(){
        return length*width;
    }
};

int main(int argc,char *argv[])
{
    Rectangle R1(2,3);
    cout<<"周长等于："<<R1.calcPerimeter()<<endl;
    cout<<"面积等于："<<R1.calcArea()<<endl;
    return 0;
}


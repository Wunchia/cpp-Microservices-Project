#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class Complex{
public:
    Complex(int real,int image)
    :_real(real)
    ,_image(image)
    {}

    void print()const{
        cout<<_real<<"+"<<_image<<"i"<<endl;
    }

private:
    int _real;
    int _image;
};

class Point{
public:
    Point(int x,int y)
    :_x(x)
    ,_y(y)
    {}

    operator Complex(){
        return Complex{_x,_y};
    }

private:
    int _x;
    int _y;
};

int main(int argc,char *argv[])
{
    Point pt(8,9);
    Complex cx(4,6);
    cx = pt;
    cx.print(); 
    return 0;
}


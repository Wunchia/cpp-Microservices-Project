#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class Point;

class Complex
{
public:
    Complex(int real, int image)
    : _real(real)
    , _image(image)
    {}

    void print()const{
        cout<<_real<<"+"<<_image<<"i"<<endl;
    }

    Complex(const Point& rhs);

private:
    int _real;
    int _image;
};

class Point
{
public:
    Point(int x, int y)
    : _x(x)
    , _y(y)
    {}


    friend Complex::Complex(const Point&);

private:
    int _x;
    int _y;
};

Complex::Complex(const Point &rhs)
:_real(rhs._x)
,_image(rhs._y)
{
    cout<<"Complex(const Point&)"<<endl;
}

int main(int argc, char *argv[])
{
    Point pt{8,9};
    Complex cx{4,6};
    cx=pt;
    cx.print();

    return 0;
}

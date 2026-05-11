#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class Point;
class Complex{
public:
    Complex(int real,int image)
    :_real(real)
    ,_image(image)
    {}

    Complex& operator=(const Point&rhs);

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

friend Complex& Complex::operator=(const Point&);
private:
    int _x;
    int _y;
};

Complex& Complex::operator=(const Point&rhs){
    cout<<"Complex&operator=(const Point&)"<<endl;
    this->_real=rhs._x;
    this->_image=rhs._y;
    return *this;
}

int main(int argc,char *argv[])
{
    Point pt(8,9);
    Complex cx(4,6);
    cx = pt;
    cx.print(); 
    return 0;
}


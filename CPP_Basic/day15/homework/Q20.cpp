#include <iostream>
#include <string>
#include <cmath>
using std::string;
using std::cin;
using std::cout;
using std::endl;
//编写程序：给定以下抽象类Figure，
//通过该图形类扩展生成3个不同的图形Rectangle、Circle、Triangle，体会使用纯虚函数的好处。

class Figure {
public:
    virtual string getName() const = 0;
    virtual double getArea() const = 0;
};

class Rectangle:public Figure
{
public:
    Rectangle(double length,double width)
    :_length(length)
    ,_width(width)
    {}

    virtual string getName()const override{
        return "Rectangle";
    }
    virtual double getArea()const override{
        return _length*_width;
    }
private:
    double _length;
    double _width;
};

class Circle : public Figure
{
public:
    Circle(double r)
    :_r(r)
    {}
    virtual string getName()const override{
        return "Circle";
    }
    virtual double getArea()const override{
        return 3.14*_r*_r;
    }

private:
    double _r;
};

class Triangle : public Figure
{
public:
    Triangle(double l_1,double l_2,double l_3)
    :_line1(l_1)
    ,_line2(l_2)
    ,_line3(l_3)
    {}

    virtual string getName()const override{
        return "Triangle";
    }
    virtual double getArea()const override{
        double p=(_line1+_line2+_line3)/2;
        return sqrt(p*(p-_line1)*(p-_line2)*(p-_line3));
    }

private:
    double _line1;
    double _line2;
    double _line3;
};

void display(Figure & fig) {
    cout << fig.getName() 
         << "的面积是:" 
         << fig.getArea() << endl ;
}

void test() {
    Rectangle r(10, 20);
    Circle c(15);
    Triangle t(3, 4, 5);
    display(r);
    display(c);
    display(t);
}
int main(int argc,char *argv[])
{
    test();
    return 0;
}


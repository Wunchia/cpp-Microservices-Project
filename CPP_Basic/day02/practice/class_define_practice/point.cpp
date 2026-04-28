#include <iostream>
#include "point.hpp"
using std::cin;
using std::cout;
using std::endl;

void Point::setX(int x){_x=x;}
int Point::getX()const{return _x;}

int main(int argc,char *argv[])
{
    Point p;
    p.setX(1);
    cout<<p.getX()<<endl;
    return 0;
}


#include <iostream>
#include <cstring>
#include <cmath>
using std::cin;
using std::cout;
using std::endl;

/*
定义一个点Point类，数据成员是横纵坐标（float）；
定义一个颜色类Color数据成员只有颜色（char*）；
一个直线类Line，数据成员是两个Point对象，表示起点和终点（即Point两个对象为Line的内嵌对象）；
一个三角形类Triangle，继承自Line和Color，数据成员有三角形的高height（float），
三角形理解成以基类Color为颜色，以基类直线为底，以height为高的直角三角形，(即直线和高分别为两条直角边)
请实现相关函数，计算三角形的颜色、周长和面积并给出相关输出
*/

class Point{
public:
    Point(float x=0,float y=0)
    :_x(x)
    ,_y(y)
    {}

    Point &operator=(const Point& rhs){
        if(this!=&rhs){
            this->_x=rhs._x;
            this->_y=rhs._y;
        }
        return *this;
    }

    float getX()const{
        return _x;
    }

    float getY()const{
        return _y;
    }

private:
    float _x;
    float _y;
};

class Color{
public:
    Color()
    :_color(nullptr)
    {}

    Color(const char* color)
    :_color(new char[strlen(color)+1])
    {
        strcpy(_color,color);
    }

    Color(const Color&rhs)
    :_color(new char[strlen(rhs._color)+1])
    {
        strcpy(_color,rhs._color);
    }

    Color& operator=(const Color&rhs){
        if(this!=&rhs){
            if(rhs._color){
                char* temp=new char[strlen(rhs._color)+1];
                strcpy(temp,rhs._color);
                delete[] _color;
                _color=temp;
            }else{
                delete[] _color;
                _color=nullptr;
            }
        }
        return *this;
    }

    virtual ~Color(){
        delete[] _color;
    }

    char* getColor()const{
        return _color;
    }

private:
    char* _color;
};

class Line{
public:
    Line(Point a,Point b)
    :_start(a)
    ,_end(b)
    {}

    Line(const Line&rhs)
    :_start(rhs._start)
    ,_end(rhs._end)
    {}

    virtual ~Line(){}

    float getLength()const{
        return sqrt(pow((_start.getX()-_end.getX()),2)+pow((_start.getY()-_end.getY()),2));
    }
private:
    Point _start;
    Point _end;
};

class Triangle
:public Line
,public Color 
{
public:
    Triangle(const Line& line,const Color& color,float height)
    :Line(line)
    ,Color(color)
    ,_height(height)
    {}

    float getArea()const{
        return (_height*getLength())/2;
    }

    float getPerimeter()const{
        return (_height+getLength()+sqrt(pow(_height,2)+pow(getLength(),2)));
    }

private:
    float _height;
};

int main(int argc,char *argv[])
{
    Point a{1,1};
    Point b{4,1};
    
    Line L1{a,b};
    
    Color color{"blue"};

    Triangle T{L1,color,4.0};

    cout<<"Color:"<<T.getColor()<<endl;
    cout<<"Area:"<<T.getArea()<<endl;
    cout<<"Perimeter:"<<T.getPerimeter()<<endl;

    return 0;
}


#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class Point{
public:
    static Point &getSingleton(){
        static Point instance;
        return instance;
    }

    Point& operator=(const Point&)=delete;
    Point(const Point&)=delete; 
private:
    Point(){}
};

int main(int argc,char *argv[])
{
    Point &p1=Point::getSingleton();
    Point &p2=Point::getSingleton();
    cout<<&p1<<endl;
    cout<<&p2<<endl;
    return 0;
}


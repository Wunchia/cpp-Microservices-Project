#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;

class Point{
public:
    Point(int x,int y)
    :m_x(x)
    ,m_y(y)
    {}

    void print()const{
        cout<<m_x<<" "<<m_y<<endl;
    }

private:
    int m_x;
    int m_y;
};

int main(int argc,char *argv[])
{
    vector<Point> v1{{1,2},{3,4},{5,6}};
    
    for(const auto&it:v1){
        it.print();
    }
    return 0;
}


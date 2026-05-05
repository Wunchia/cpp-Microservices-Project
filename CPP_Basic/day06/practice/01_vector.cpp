#include <iostream>
#include <vector>
#include <list>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::list;

class Point{
public:
    Point(int x,int y)
    :_x(x)
    ,_y(y)
    {}
private:
    int _x;
    int _y;
};

void testVectorConstruct(){
    vector<int> v1;
    vector<int> v2={1,2,3,4,5};
    vector<int> v3(v2);
    list<int> l={10,20,30};
    vector<int> v4(l.begin(),l.end());
    vector<int> v5(5,100);
    vector<Point> v6;
    v6.emplace_back(1,2);
}

int main(int argc,char *argv[])
{
    testVectorConstruct();
    return 0;
}


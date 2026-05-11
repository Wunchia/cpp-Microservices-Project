#include <iostream>
using std::cin;
using std::cout;
using std::endl;

//外部类  寄居蟹的壳
class Line{
private:
    //内部类 寄居蟹
    class Point{
    public:
        Point(int x,int y)
        :m_x(x)
        ,m_y(y)
        {}

        void print()const{
            cout<<"["<<m_x<<" , "<<m_y<<"]";
        }

    private:
        int m_x;
        int m_y;
    };

public:
    Line()=default;
    Line(int x1,int y1,int x2,int y2)
    :m_pt1{x1,y1}
    ,m_pt2{x2,y2}
    {}

    void print()const{
        cout<<"{";
        m_pt1.print();
        cout<<" ; ";
        m_pt2.print();
        cout<<"}"<<endl;
    }

private:
    Point m_pt1;
    Point m_pt2;
};


void test1(){
    Line L1{1,2,3,4};
    cout<<sizeof(L1)<<endl;
    L1.print();
}

int main(int argc,char *argv[])
{
    test1();    
    return 0;
}


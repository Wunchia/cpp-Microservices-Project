#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class Point{
public:
    static Point* getInstance(const int x,const int y){
        if(!ms_instance){
            ms_instance=new Point(x,y);
        }
        return ms_instance;
    }

    static void altInstance(const int x,const int y){
        if(!ms_instance){
            return;
        }
        ms_instance->m_x=x;
        ms_instance->m_y=y;
    }

    static void destroyInstance(){
        if(ms_instance){
            delete ms_instance;
            ms_instance=nullptr;
        }
    }

    void print()const{
        cout<<m_x<<" "<<m_y<<endl;
    }

    Point(const Point&)=delete;
    Point& operator=(const Point&)=delete;
private:
    int m_x;
    int m_y;
    Point(int x,int y)
    :m_x(x)
    ,m_y(y)
    {};
    static Point* ms_instance;
};

Point * Point::ms_instance=nullptr;

int main(int argc,char *argv[])
{
    Point* p1=Point::getInstance(1,1);
    p1->print();
    Point* p2=Point::getInstance(2,2);
    p2->print();
    cout<<p1<<endl<<p2<<endl;

    Point::altInstance(1,2);
    p1->print();
    Point::altInstance(3,4);
    p1->print();

    Point::destroyInstance();
    p1=p2=nullptr;

    cout<<p1<<endl<<p2<<endl;

    return 0;
}


#include <iostream>
#include <set>
using namespace std;

//=======写法一：重载 小于运算符=======
struct PointA{
    int _x;
    int _y;

    PointA(int x=0,int y=0)
    :_x(x)
    ,_y(y)
    {}

    bool operator<(const PointA& rhs) const{
        if(this->_x==rhs._x){
            return this->_y<rhs._y;
        }
        return this->_x<rhs._x;
    }
};

//=======写法二：仿函数=======
struct PointB{
    int _x;
    int _y;
    PointB(int x=0,int y=0)
    :_x(x)
    ,_y(y)
    {}
};

struct ComparePointB{
    bool operator()(const PointB& lhs,const PointB& rhs) const{
        if(lhs._x==rhs._x){
            return lhs._y<rhs._y;
        }
        return lhs._x<rhs._x;
    }
};

//=======写法三：lambda表达式=======
struct PointC{
    int _x;
    int _y;
    PointC(int x=0,int y=0)
    :_x(x)
    ,_y(y)
    {}
};

namespace std
{
    template<>
    struct less<PointC>  // 针对Student类型进行特殊处理
    {
        bool operator()(const PointC & lhs, const PointC & rhs) const
        {
            if(lhs._x==rhs._x){
                return lhs._y<rhs._y;
            }
            return lhs._x<rhs._x;
        }
    };



}

int main(int argc,char *argv[])
{
    //-------- 测试写法一 ---------
    cout<<"=====测试写法一======"<<endl;
    set<PointA> s1;
    s1.insert(PointA(2,3));
    s1.insert(PointA(3,4));
    s1.insert(PointA(2,1));

    for(const auto& e:s1){
        cout<<e._x<<","<<e._y<<endl;
    }
    cout<<"=====结束======"<<endl;

    //-------- 测试写法二 ---------
    cout<<"=====测试写法二======"<<endl;
    set<PointB,ComparePointB> s2;
    s2.insert(PointB(2,3));
    s2.insert(PointB(3,4));
    s2.insert(PointB(2,1));

    for(const auto& e:s2){
        cout<<e._x<<","<<e._y<<endl;
    }
    cout<<"=====结束======"<<endl;

    //-------- 测试写法三 ---------
    cout<<"=====测试写法三======"<<endl;

    set<PointC> s3;
    s3.insert(PointC(2,3));
    s3.insert(PointC(3,4));
    s3.insert(PointC(2,1));

    for(const auto& e:s3){
        cout<<e._x<<","<<e._y<<endl;
    }
    cout<<"=====结束======"<<endl;

    return 0;
}


#include <iostream>
#include <vector>
#include <algorithm>
using std::cin;
using std::cout;
using std::endl;
using std::vector;

class CountEven{
public:
    CountEven()
    :m_count(0)
    ,m_callCount(0)
    {}

    void operator()(int val){
        m_callCount++;
        if(val%2==0){
            m_count++;
        }
    }

    int getCount()const{
        return m_count;
    }

    int getCallCount()const{
        return m_callCount;
    }
private:
    int m_count;
    int m_callCount;
};

int main(int argc,char *argv[])
{
    vector<int> vec{1,2,3,4,5,6,7,8,9,10};

    CountEven countEvenObj;

    countEvenObj=std::for_each(vec.begin(),vec.end(),countEvenObj);
    
    cout<<"总调用次数："<<countEvenObj.getCallCount()<<endl;

    cout<<"偶数总个数："<<countEvenObj.getCount()<<endl;

    return 0;
}


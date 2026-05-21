#include <iostream>
#include <list>
#include <deque>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

//编写程序，从一个 list 拷贝元素到两个 deque 中。
//值为偶数的所有元素都拷贝到一个 deque 中，
//而奇数值元素都拷贝到另一个 deque 中。

template <typename T>
void print(const T&t){
    for(const auto&e:t){
        cout<<e<<" ";
    }
    cout<<endl;
}

void test(){
    list<int> box{3,1,2,4,7,8,5,9};
    deque<int> deq1,deq2;
    for(auto &e:box){
        if(e%2==0){
            deq1.push_back(e);
        }else{
            deq2.push_back(e);
        }
    }
    print(deq1);
    print(deq2);
}

int main(int argc,char *argv[])
{
    test();    
    return 0;
}


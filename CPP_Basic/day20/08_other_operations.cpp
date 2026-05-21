#include <iostream>
#include <vector>
#include <list>
#include <deque>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

template<typename T>
void print(T &t){
    for(auto &e:t){
        cout<<e<<" ";
    }
    cout<<endl;
}

void test1(){
    list<int> box{1,2,3,4,5};
    print(box);
    cout<<"box.size()="<<box.size()<<endl;
    box.clear();
    print(box);
    cout<<"box.size()="<<box.size()<<endl;
}

void test2(){
    // list<int> box1{1,2,3,4,5};
    // list<int> box2{6,7,8};
    vector<int> box1{1,2,3,4,5};
    vector<int> box2{6,7,8};
    print(box1);
    print(box2);
    cout<<"---swap---"<<endl;
    box1.swap(box2);
    print(box1);
    print(box2);
} 

//resize()更改元素个数
void test3(){
    list<int> box{1,2,3,4,5};
    print(box);
    cout<<"box.size()="<<box.size()<<endl;
    box.resize(10);
    cout<<"----resize----"<<endl;
    print(box);
    cout<<"box.size()="<<box.size()<<endl;
}

//shrink_to_fit()压缩容器大小
void test4(){
    vector<int> box{1,2,3,4,5};
    cout<<"box.capacity()="<<box.capacity()<<endl;
    cout<<"box.size()="<<box.size()<<endl;
    box.reserve(10);
    cout<<"----reserve----"<<endl;
    cout<<"box.capacity()="<<box.capacity()<<endl;
    cout<<"box.size()="<<box.size()<<endl;
    box.shrink_to_fit();
    cout<<"----shrink_to_fit----"<<endl;
    cout<<"box.capacity()="<<box.capacity()<<endl;
    cout<<"box.size()="<<box.size()<<endl;
}

int main(int argc,char *argv[])
{
    // test1();
    // test2();
    // test3();
    test4();
    return 0;
}


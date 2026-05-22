#include <iostream>
#include <deque>
using std::deque;
using std::cin;
using std::cout;
using std::endl;

template <typename Container>
void print(const Container &c){
    for(auto &e:c){
        cout<<" "<<e;
    }
    cout<<endl;
}

void practiceDeque(){
    cout<<"========deque practice========"<<endl;

    //常用API测试
    deque<int> d={20,30,40};
    d.push_front(10);
    d.push_back(50);
    
    d[2]=99;
    print(d);
    d.pop_front();
    d.pop_back();
    print(d);

    //迭代器失效规则
    deque<int> d1={1,2,3};
    auto it=d1.begin()+1;
    int*ptr=&d1[1];

    //场景A：在头尾插入元素
    d1.push_front(0);
    d1.push_back(4);
    cout<<*it<<endl;//在两端插入可能会导致所有迭代器失效
    //因为中控器 map 可能会重新分配
    cout<<*ptr<<endl;//但指向元素的指针和引用依然有效
    //因为数据块本身没有被移动

    //场景B：在中间插入/删除元素
    d1.insert(d1.begin()+2,99);
    //在中间插入或删除，不仅迭代器失效，所有的指针和引用也会失效
    cout<<*it<<endl;
    cout<<*ptr<<endl;
}

int main(int argc,char *argv[])
{
    practiceDeque();
    return 0;
}


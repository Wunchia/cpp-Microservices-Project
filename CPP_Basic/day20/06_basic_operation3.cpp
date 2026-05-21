#include <iostream>
#include <vector>
#include <list>
#include <deque>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::list;
using std::deque;

template <typename Container>
void print(Container &box){
    for(auto & e:box){
        cout<<e<<" ";
    }
    cout<<endl;
}

//list erase 操作
void test1(){
    list<int> box{1,2,3,4,5,6,7};
    print(box);
    auto it=box.begin();
    ++it;
    ++it;
    box.erase(it);
    print(box);
    cout<<"*it="<<*it<<endl;
}

//list erase操作 更新迭代器
void test2(){
    list<int> box{1,2,3,4,5,6,7};
    print(box);
    auto it=box.begin();
    ++it;
    ++it;
    it=box.erase(it);
    print(box);
    cout<<"*it="<<*it<<endl;
    auto itBegin=box.begin();
    auto itEnd=box.end();
    --itEnd;
    --itEnd;
    auto it2=box.erase(itBegin,itEnd);
    print(box);
    cout<<"*it2="<<*it2<<endl;
}

//deque erase 操作 不更新迭代器
void test3(){
    deque<int> box{1,2,3,4,5,6,7};
    print(box);
    auto it=box.begin();
    ++it;
    ++it;
    cout<<"*it="<<*it<<endl;

    box.erase(it);
    print(box);
    cout<<"*it="<<*it<<endl;

    box.erase(it);
    print(box);
    cout<<"*it="<<*it<<endl;
}

//deque erase 操作 更新迭代器
void test4(){
    deque<int> box{1,2,3,4,5,6,7};
    print(box);
    auto it=box.begin();
    ++it;
    ++it;
    cout<<"*it="<<*it<<endl;

    it=box.erase(it);
    print(box);
    cout<<"*it="<<*it<<endl;

    it=box.erase(it);
    print(box);
    cout<<"*it="<<*it<<endl;
}

void test5(){
    vector<int> box{1,2,3,4,5,6,7};
    print(box);
    auto it=box.begin();
    ++it;
    ++it;
    cout<<"*it="<<*it<<endl;

    it=box.erase(it);
    print(box);
    cout<<"*it="<<*it<<endl;

    it=box.erase(it);
    print(box);
    cout<<"*it="<<*it<<endl;

    it=box.erase(it);
    print(box);
    cout<<"*it="<<*it<<endl;

    it=box.erase(it);
    print(box);
    cout<<"*it="<<*it<<endl;

    it=box.erase(it);
    print(box);
    cout<<"*it="<<*it<<endl;
}

//删除重复的3
void test6(){
    vector<int> box{1,2,3,3,3,3,4,5,6};
    print(box);
    for(auto it=box.begin();it!=box.end();){
        if(*it==3){
            it=box.erase(it);
        }else{
            ++it;
        }
    }
    print(box);
}

int main(int argc,char *argv[])
{
    // test1();
    // test2();
    // test3();
    // test4();
    // test5();
    test6();
    return 0;
}

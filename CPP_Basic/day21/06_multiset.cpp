#include <iostream>
#include <set>
#include <list>
using std::list;
using std::set;
using std::multiset;
using std::cin;
using std::cout;
using std::endl;

/*
关联式容器：底层结构是红黑树
set：无重复元素的集合 升序排序
multiset：有重复元素的集合 升序排序
map：键值对的集合 升序排序 key唯一 value可以重复
multimap：键值对的集合 升序排序 key可以重复 value可以重复
*/

template <typename Container>
void print(Container &box){
    for(auto &e:box){
        cout<<" "<<e;
    }
    cout<<endl;
}

//容器的构建
void test1(){
    //无参构造
    multiset<int> box1;
    //初始化列表
    multiset<int> box2{3,1,2,5,4};
    //拷贝构造
    // set<int> box3=box2;
    multiset<int> box3(box2);
    //迭代器
    multiset<int> box4{box2.begin(),box2.end()};
    print(box2);
}

//insert
void test2(){
    multiset<int> box;
    auto it=box.insert(2);
    cout<<"*it="<<*it<<endl;
    box.insert(3);
    box.insert(1);
    box.insert(2);
    box.insert(5);
    box.insert(4);
    print(box);
    cout<<"----------"<<endl;
    list<int>box2{10,20,30};
    box.insert(box2.begin(),box2.end());
    print(box);
    cout<<"----------"<<endl;
    box.insert({100,200});
    print(box);
}

//count / find
void test3(){
    multiset<int> box{1,2,3,3,3,4,5};
    print(box);
    //count：统计元素出现的次数 找到了返回1 未找到返回0
    cout<<box.count(3)<<endl;
    cout<<box.count(6)<<endl;
    //find：查找元素 找到了返回迭代器 未找到返回end()
    auto it=box.find(3);
    if(it!=box.end()){
        cout<<"找到"<<*it<<endl;
    }else{
        cout<<"未找到"<<endl;
    }
}

//erase
void test4(){
    multiset<int> box{1,2,3,4,5};
    //erase：删除元素 找到了返回删除的元素 未找到返回end()
    auto it=box.begin();
    ++it;
    it=box.erase(it);
    if(it!=box.end()){
        cout<<"删除成功"<<endl;
    }else{
        cout<<"未找到"<<endl;
    }
    print(box);
}

//set不支持下标访问
void test5(){
    multiset<int> box{1,2,3,4,5};
    //set不支持下标访问
    // cout<<box[3]<<endl;
    auto it=box.begin();
    cout<<"*it="<<*it<<endl;
    //不支持通过迭代器进行修改
    // *it=10;//表达式必须是可修改的左值
}


int main(int argc,char *argv[])
{
    // test1();    
    // test2();
    // test3();
    test4();
    return 0;
}


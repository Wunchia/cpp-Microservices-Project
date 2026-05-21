#include <iostream>
#include <vector>
#include <array>
#include <forward_list>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

/*
容器分类：
    1. 顺序容器（Sequence Containers）：底层实现各不相同
        array：        静态数组（连续内存，大小固定）
        vector：       动态数组（连续内存，支持尾部动态扩容）
        forward_list： 单向链表（非连续内存，只支持单向遍历）
        list：         双向链表（非连续内存，支持双向遍历）
        deque：        双端队列（分段连续内存，头尾皆可高效插入删除）

    2. 关联容器（Associative Containers）：
       元素自动排序，底层实现通常是红黑树（RB-Tree）
        set：          集合（键即值，键唯一）
        map：          映射（键值对，键唯一）
        multiset：     多重集合（键即值，键可重复）
        multimap：     多重映射（键值对，键可重复）

    3. 无序关联容器（Unordered Associative Containers）：
       底层实现是哈希表（Hash Table）
        unordered_set
        unordered_map
        unordered_multiset
        unordered_multimap
*/

//了解array,forward_list
void test1(){
    array<int,5> arr{1,2,3,4,5};
    cout<<arr[0]<<endl;
    cout<<arr.at(1)<<endl;
    cout<<arr.front()<<endl;
    cout<<arr.back()<<endl;
    cout<<"--------------------"<<endl;

    forward_list<int> fl{4,5,6};
    for(auto & e:fl){
        cout<<e<<" ";
    }
    cout<<endl;
}

int main(int argc,char *argv[])
{
    test1();    
    return 0;
}


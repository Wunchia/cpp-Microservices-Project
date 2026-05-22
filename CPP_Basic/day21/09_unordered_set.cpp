#include <iostream>
#include <unordered_set>
#include <string>
using std::unordered_set;
using std::string;
using std::cin;
using std::cout;
using std::endl;

/*
无序关联式容器：底层使用的是哈希表
unorderd_set: 无序集合容器 元素是唯一的
unorderd_multiset: 无序多集合容器 元素可以重复

unorderd_map: 无序映射容器 key是唯一的
unorderd_multimap: 无序多映射容器 key可以重复
*/

template<typename Container>
void print(const Container &c){
    for(auto &e:c){
        cout<<" "<<e;
    }
    cout<<endl;
}


//容器的构建
void test1(){
    unordered_set<int> box{1,2,3,3,4,5};
    print(box);
}

void test2(){
    unordered_set<int> box;
    // 插入元素
    box.insert(1);
    box.insert(2);
    box.insert(3);
    //查找元素
    int result=box.count(3);
    //删除元素
    box.erase(box.begin());
    auto it= box.find(3);
    print(box);
}

int main(int argc,char *argv[])
{
    // test1();
    test2();
    return 0;
}


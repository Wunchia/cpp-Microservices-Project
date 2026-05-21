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

//insert 插入元素
void test1(){
    //iterator insert(iterator pos,const T &value);
    vector<int> box{1,2,3,4,5};
    cout<<"size="<<box.size()<<endl;
    cout<<"capacity="<<box.capacity()<<endl;
    print(box);
    //给定位置 插入单个元素
    auto it=box.begin();
    ++it;//it指向扩容前的第二个元素
    // box.insert(it,100);//插入过程中 vector发生了扩容
    it=box.insert(it,100);//更新迭代器
    cout<<"size="<<box.size()<<endl;
    cout<<"capacity="<<box.capacity()<<endl;
    print(box);
    cout<<"*it="<<*it<<endl;//迭代器可能会失效 需要更新

    //void insert(iterator pos,size_type count,const T &value);
    it=box.insert(it,2,10);//更新迭代器
    print(box);
    cout<<"*it="<<*it<<endl;//指向首个被插入的元素
    ++it;
    cout<<"*it="<<*it<<endl;//指向首个被插入的元素的下一个元素
    ++it;
    cout<<"*it="<<*it<<endl;//指向首个被插入的元素的下一个元素的下一个元素

    //template<class InputIt> void insert(iterator pos,InputIt first,InputIt last);
    auto it2=box.begin();
    ++it2;
    //给定位置用初始化列表插入
    box.insert(it2,{1000,2000});
    print(box);
    cout<<"*it="<<*it<<endl;//指向插入位置的下一个元素
    ++it;
    cout<<"*it="<<*it<<endl;

    //iterator insert(const_iterator pos,std::initializer_)
    vector<int> box2{10,20,30};
    print(box2);
    it2=box.insert(it2,box2.begin(),box2.end());
    print(box);
    cout<<"*it2="<<*it2<<endl;//指向首个被插入的元素

}


int main(int argc,char *argv[])
{
    test1();
    return 0;
}


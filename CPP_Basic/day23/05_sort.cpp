#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <iterator>

using namespace std;

void test1(){
    // vector<int> box{3,1,5,2,4};
    deque<int> box{3,1,5,2,4};
    sort(box.begin(),box.end());
    std::copy(box.begin(),box.end(),std::ostream_iterator<int>(cout," "));
    cout<<endl;
    //vector<Student> box;
}

// max min 返回最大最小值
void test2(){
    int a=1;
    int b=2;
    int maxValue=max(a,b);
    cout<<"maxValue="<<maxValue<<endl;
    cout<<"-------------"<<endl;
    int minValue=min(a,b);
    cout<<"minValue="<<minValue<<endl;
    vector<int> box{3,1,5,2,4};
    int max_num=*max_element(box.begin(),box.end());
    int min_num=*min_element(box.begin(),box.end());
    cout<<"max_num="<<max_num<<endl;
    cout<<"min_num="<<min_num<<endl;
}

//lower_bound 二分查找第一个大于等于目标值的元素
//upper_bound 二分查找第一个大于目标值的元素
//equal_range 二分查找等于目标值的元素范围 返回pair<lower_bound,upper_bound>
void test3(){
    vector<int> box{1,2,3,4,5};
    auto it1=lower_bound(box.begin(),box.end(),3);
    cout<<"*it1="<<*it1<<endl;
    cout<<"-------------"<<endl;
    auto it2=upper_bound(box.begin(),box.end(),3);
    cout<<"*it2="<<*it2<<endl;
    cout<<"-------------"<<endl;
    auto it3=equal_range(box.begin(),box.end(),3);
    cout<<"*it3.first="<<*it3.first<<endl;
    cout<<"*it3.second="<<*it3.second<<endl;

}

//集合操作 ： 并集 交集 ……
void test4(){
    vector<int> box1{1,2,3,4,5};
    vector<int> box2{3,4,5,6,7};
    vector<int> box3;
    //并集
    set_union(box1.begin(),box1.end(),box2.begin(),box2.end(),back_inserter(box3));
    std::copy(box3.begin(),box3.end(),std::ostream_iterator<int>(cout," "));
    cout<<endl;
}

//集合操作 ： 并集 交集 ……
void test5(){
    vector<int> box1{1,2,3,4,5};
    vector<int> box2{3,4,5,6,7};
    vector<int> box3;
    //交集
    set_intersection(box1.begin(),box1.end()
                    ,box2.begin(),box2.end()
                    ,back_inserter(box3));
    std::copy(box3.begin(),box3.end(),std::ostream_iterator<int>(cout," "));
    cout<<endl;
}


int main(int argc,char *argv[])
{
    //test1();
    // test2();
    // test3();
    test4();
    test5();
    return 0;
}


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

//vector 初始化
void test1(){
    //无参构造
    vector<int> box1;
    //初始化列表
    vector<int> box2{1,2,3,4,5};
    //拷贝构造
    vector<int> box3(box2);
    // vector<int> box3=box2;
    //迭代器范围
    vector<int> box4(box2.begin(),box2.end());
    //count个value
    vector<int> box5(5,100);
    print(box2);
}

//list 初始化
void test2(){
    //无参构造
    list<int> box1;
    //初始化列表
    list<int> box2{1,2,3,4,5};
    //拷贝构造
    list<int> box3(box2);
    // list<int> box3=box2;
    //迭代器范围
    list<int> box4(box2.begin(),box2.end());
    //count个value
    list<int> box5(5,100);
    print(box2);
}

//deque 初始化
void test3(){
    //无参构造
    deque<int> box1;
    //初始化列表
    deque<int> box2{1,2,3,4,5};
    //拷贝构造
    deque<int> box3(box2);
    // deque<int> box3=box2;
    //迭代器范围
    deque<int> box4(box2.begin(),box2.end());
    //count个value
    deque<int> box5(5,100);
    print(box2);
}

void test4(){
    cout<<"------vector------"<<endl;
    vector<int> box1{1,2,3,4,5};
    //for i 下标 进行遍历
    for(int i=0;i<box1.size();i++){
        cout<<box1[i]<<" ";
    }
    cout<<endl;

    //迭代器遍历
    for(auto it=box1.begin();it!=box1.end();it++){
        cout<<*it<<" ";
    }
    cout<<endl;

    //foreach 遍历
    for(auto & e:box1){
        cout<<e<<" ";
    }
    cout<<endl;

    cout<<"------list------"<<endl;
    list<int> box2{1,2,3,4,5};
    
    //for i 下标 进行遍历
    // for(int i=0;i<box2.size();i++){
    //     cout<<box2[i]<<" ";//报错 list容器不支持下标访问
    // }
    // cout<<endl;

    //迭代器遍历
    for(auto it=box2.begin();it!=box2.end();it++){
        cout<<*it<<" ";
    }
    cout<<endl;
    
    //foreach 遍历
    for(auto & e:box2){
        cout<<e<<" ";
    }
    cout<<endl;

    cout<<"------deque------"<<endl;
    deque<int> box3{1,2,3,4,5};

    //for i 下标 进行遍历
    for(int i=0;i<box3.size();i++){
        cout<<box3[i]<<" ";
    }
    cout<<endl;

    //迭代器遍历
    for(auto it=box3.begin();it!=box3.end();it++){
        cout<<*it<<" ";
    }
    cout<<endl;

    //foreach 遍历
    for(auto & e:box3){
        cout<<e<<" ";
    }
    cout<<endl;
}

//push_back / pop_back
void test5(){
    // vector<int> box1{1,2,3};
    // list<int> box1{1,2,3};
    deque<int> box1{1,2,3};
    print(box1);
    box1.push_back(4);
    box1.push_back(5);
    print(box1);
    box1.pop_back();
    print(box1);
}

//push_front / pop_front
void test6(){
    // vector<int> box1{1,2,3};//vector容器不支持头插插入
    // list<int> box1{1,2,3};
    deque<int> box1{1,2,3};
    print(box1);
    box1.push_front(0);
    box1.push_front(1);
    print(box1);
    box1.pop_front();
    print(box1);
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


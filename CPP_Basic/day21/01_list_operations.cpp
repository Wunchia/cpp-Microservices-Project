#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <string>
#include <functional>
#include <algorithm>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

template<typename T>
void print(const T &t){
    for(const auto &e:t){
        cout<<" "<<e;
    }
    cout<<endl;
}

//list中的特有操作 sort() 排序
//默认是升序排序
void test1(){
    list<int> box{3,1,2,5,4};
    print(box);
    // box.sort();// vector中没有sort方法
    box.sort();
    print(box);
}

class Student{
public:
    Student(int id,string name,int age)
    :_id(id),_name(name),_age(age)
    {
        cout<<"Student(int,string,int)"<<endl;
    }

    //operator<<
    friend ostream& operator<<(ostream &os,const Student &s);

    bool operator<(const Student&other)const{
        return this->_id<other._id;
    }

    int _id;
    string _name;
    int _age;
};

ostream& operator<<(ostream &os,const Student &s){
    os<<"_id="<<s._id<<" _name="<<s._name<<" _age="<<s._age<<endl;
    return os;
}

void test2(){
    Student s1(2,"张三",19);
    Student s2(3,"李四",21);
    Student s3(1,"王五",20);
    list<Student> box{s1,s2,s3};
    print(box);
    box.sort();
    print(box);
}

//自定义比较器
struct StudentCompare{
    bool operator()(const Student&lhs,const Student&rhs){
        return lhs._age>rhs._age;
    }
};

void test3(){
    Student s1(2,"张三",19);
    Student s2(3,"李四",21);
    Student s3(1,"王五",20);
    list<Student> box{s1,s2,s3};
    print(box);
    box.sort(StudentCompare());
    print(box);
}

void test4(){
    list<int> box{3,1,2,5,4};
    print(box);
    box.sort(greater<int>());
    print(box);
}

//如果不是list，怎么排序
void test5(){
    vector<int> box1{3,1,2,5,4};
    deque<int> box2{3,1,2,5,4};
    print(box1);
    print(box2);
    //box.sort(greater<int>());//vector或deque中没有sort方法
    //可以使用算法库中的sort函数
    sort(box1.begin(),box1.end(),greater<int>());
    print(box1);
    sort(box2.begin(),box2.end(),greater<int>());
    print(box2);
}

int main(int argc,char *argv[])
{
    // test1();
    // test2();
    // test3();
    // test4();
    test5();
    return 0;
}


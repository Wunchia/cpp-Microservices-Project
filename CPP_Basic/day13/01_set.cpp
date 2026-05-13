#include <iostream>
#include <set>
#include <utility>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::set;
using std::pair;
using std::string;

/*
 * set容器：底层是红黑树
 * 特点：
 * 1.存储的数据是单列数据 一个一个
 * 2.元素不能重复 元素是有序的 默认按照升序排列
 * 
 * 使用场景：
 * 1.去重
 * 2.排序
 * 
 * map容器：存储的是双列数据（一对一对）
 * key-value数据：键值对数据
 * 属性名=属性值
 * name="zs"
 * city="BJ"
 * age=20
 * 
 * 
 * set的使用：
 * 存储数据时 类似vector 需要指明数据的类型是什么
 * set<int>
 * set<Student>
 * set<string>
 * 
 */

//set容器的构建
void test1(){
    //无参构造函数--->空容器
    set<int> box1;
    
    //初始化列表方式
    set<int> box2{3,1,2,5,4};

    //迭代器方式
    set<int> box3{box2.begin(),box2.end()};

    //拷贝构造
    set<int> box4=box3;
}

//验证set容器的特点
void test2(){
    set<int> box{3,1,2,1,5,2,5,4};
    for(auto&e:box){
        cout<<e<<" ";
    }
    cout<<endl;
    //数据是有序的（升序） 且元素不能重复
}

//元素查找 count/found
void test3(){
    set<int> box{3,1,5,3,2,5,4,7};
    int result=box.count(3);
    if(result){
        cout<<"found"<<endl;
    }else{
        cout<<"not found"<<endl;
    }
    cout<<"-------------"<<endl;
    // find(目标元素) 成功返回迭代器 失败返回尾迭代器
    // set<int>::iterator
    auto it=box.find(3);
    if(it != box.end()){
        cout<<"found"<<endl;
        cout<<*it<<endl;
    }else{
        cout<<"not found"<<endl;
    }
}

void visitSet(set<int> box){
    for(auto &it:box){
        cout<<it<<" ";
    }
    cout<<endl;
}

void visitSet2(set<int> box){
    for(auto it=box.begin();it!=box.end();++it){
        cout<<*it<<" ";
    }
    cout<<endl;
}

//insert 插入
void test4(){
    set<int> box;
    //单个数据插入
    box.insert(1);
    box.insert(2);
    box.insert(3);
    visitSet(box);

    //批量插入
    //初始化列表方式
    box.insert({5,4,7,8});
    visitSet(box);
    set<int> box2{10,11,12};
    //还可以使用迭代器插入
    box.insert(box2.find(11),box2.end());
    visitSet(box);
    cout<<"-------------------"<<endl;
    pair<set<int>::iterator,bool>p=box.insert(100);
    if(p.second){
        cout<<"insert success!"<<endl;
        cout<<*(p.first)<<endl;
    }else{
        cout<<"insert failed!"<<endl;
    }
}

//pair:存储一对数据
void test5(){
    //使用时指明pair<first的类型,second的类型>
    pair<string,int> p{"age",20};
    cout<<p.first<<":"<<p.second<<endl;
}

//erase 删除
void test6(){
    set<int> box{1,2,3,4,5};
    visitSet2(box);
    auto it=box.begin();
    ++it;
    ++it;
    box.erase(it);
    visitSet2(box);
}

//如果存自定义类型的数据
class Student{
public:
    Student(int id,string name,int age)
    :_id(id)
    ,_name(name)
    ,_age(age)
    {}

    friend bool operator<(const Student&lhs,const Student&rhs);
    void print()const{
        cout<<_id<<" "<<_name<<" "<<_age<<endl;
    }
    int _id;
    string _name;
    int _age;
};

bool operator<(const Student&lhs,const Student&rhs){
    return lhs._id<rhs._id;
}

void test7(){
    set<Student>box;
    box.insert(Student{2,"zs",18});
    box.insert(Student{1,"ww",19});
    box.insert(Student{3,"ls",20});
    for(auto &it:box){
        it.print();
    }
}

int main(int argc,char *argv[])
{
    // test1();    
    // test2();
    // test3();
    // test4();
    // test5();
    // test6();
    test7();
    return 0;
}


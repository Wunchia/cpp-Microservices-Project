#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::pair;
using std::vector;

/*
 * map容器：存储的是双列数据（一对一对）
 * key-value数据：键值对数据 具有自我描述性的数据
 * 属性名=属性值
 * name="zs"
 * city="BJ"
 * age=20
 * 
 * 底层采用红黑树
 * 特点：
 * 1.key不能重复
 * 2.按key升序进行排序
 * 
 * map的使用：指明key是个什么类型 value是个什么类型
 * 
 * map<key的类型，value的类型>
 */


//map的构建
void test1(){
    //无参构造--->空容器
    map<int,string> m1;// pair<int,string>

    //通过初始化列表构建 存的是pair对象
    map<int,string> m2{
        pair<int,string>{1,"zs"},
        pair<int,string>{3,"ww"},
        pair<int,string>{2,"ls"}
    };
    //简写
    map<int,string> m3{
        {1,"zs"},
        {3,"ww"},
        {2,"ls"}
    };
    //通过make_pair函数创建一个pair对象
    map<int,string> m4{
        std::make_pair(3,"ls"),
        std::make_pair(1,"zs"),
        std::make_pair(2,"ww")
    };

    //通过迭代器方式创建
    map<int,string> m5{m4.begin(),m4.end()};

    //通过拷贝构造函数构建
    map<int,string> m6{m4};

    //更换一下类型
    map<string,string> m7;
    map<string,int> m8;
    map<string,vector<int>> m9;
}

//容器的遍历
void visitMap(map<int,string>&map){
    for(auto&p:map){
        cout<<p.first<<" "<<p.second<<" | ";
    }
    cout<<endl;
}

void visitMap2(map<int,string>&map){
    for(auto it=map.begin();it!=map.end();++it){
        cout<<(*it).first<<" "<<(*it).second<<" | ";
    }
    cout<<endl;
}

void visitMap3(map<int,string>&map){
    for(auto it=map.begin();it!=map.end();++it){
        cout<<it->first<<" "<<it->second<<" | ";
    }
    cout<<endl;
}

void test2(){
    map<int,string> map{
        {1,"zs"},
        {4,"zs"},
        {3,"ww"},
        {2,"ls"}, 
        {2,"ls"} 
    };
    visitMap3(map);
}

//map的查找
void test3(){
    map<int,string> m{
        {1,"zs"},
        {4,"zs"},
        {3,"ww"},
        {2,"ls"}, 
    };
    visitMap3(m);
    // count(目标元素的key) 找到了返回1 没找到返回0
    int result=m.count(3);
    if(result){
        cout<<"found"<<endl;
    }else{
        cout<<"not found"<<endl;
    }

    cout<<"------------------"<<endl;
    //find(目标元素的key) 返回迭代器 没找到返回尾迭代器
    auto it=m.find(3);
    if(it!=m.end()){
        cout<<"found"<<endl;
        cout<<it->first<<" "<<it->second<<endl;
    }
}

//insert
void test4(){
    map<int,string> m;
    m.insert(pair<int,string>{1,"zs"});
    m.insert(std::make_pair(2,"ls"));
    m.insert({3,"ww"});

    m.insert(
        {
            {1,"zs"},
            {4,"zs"},
            {3,"ww"},
            {2,"ls"}, 
            {5,"we"},
        }
    );
    m[4]="zss";
    cout<<m[4]<<endl;
    visitMap2(m);
}


//map支持下标访问
void test5(){
    map<int,string> m{
        {5,"we"},
        {4,"mz"}
    };
    visitMap2(m);

    m[6]="kk";
    visitMap2(m);
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


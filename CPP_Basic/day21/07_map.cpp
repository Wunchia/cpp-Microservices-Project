#include <iostream>
#include <map>
#include <list>
#include <string>
using std::ostream;
using std::pair;
using std::make_pair;   
using std::string;
using std::list;
using std::map;
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
        cout<<" ["<<e.first<<":"<<e.second<<"] ";
    }
    cout<<endl;
}

template <typename K,typename V>
void print2(map<K,V> &box){
    for(auto &e:box){
        cout<<" ["<<e.first<<":"<<e.second<<"] ";
    }
    cout<<endl;
}

class Student
{
public:
    Student(int id, string name, int age) : _id(id), _name(name), _age(age) {}

    friend ostream &operator<<(ostream &os, const Student &s)
    {
        os << "_id:" << s._id << " _name:" << s._name << " _age:" << s._age << endl;
        return os;
    }

    int _id;
    string _name;
    int _age;
};

//容器的构建
void test1(){
    //无参构造
    map<int,string> box1;

    //初始化列表
    map<int,string> box2{
        {1,"a"},
        {2,"b"},
        {3,"c"},
    };
    map<int,string> box3{
        pair<int,string>(1,"a"),
        pair<int,string>(2,"b"),
        pair<int,string>(3,"c"),
    };
    map<int,string> box4{
        make_pair(1,"a"),
        make_pair(2,"b"),
        make_pair(3,"c"),
    };

    //迭代器
    map<int,string> box5{box2.begin(),box2.end()};
    //拷贝构造
    map<int,string> box6{box2};
    map<int,string> box7=box2;
    print(box2);
}

void test2(){
    map<string,int> box{
        {"a",1},
        {"d",2},
        {"c",3},
        {"b",1},
    };
    print2(box);
    cout<<"---------------"<<endl;
    int result=box.count("a");
    cout<<"result="<<result<<endl;
    cout<<"---------------"<<endl;
    auto it=box.find("a");
    if(it!=box.end()){
        cout<<"found"<<endl;
        cout<<"key="<<it->first<<endl;
        cout<<"value="<<it->second<<endl;
    }else{
        cout<<"not found"<<endl;
    }
}

void test3(){
    map<string,int> box;
    //单个数据插入
    box.insert(pair<string,int>("a",1));
    box.insert({"d",2});
    box.insert(make_pair("c",3));
    print(box);
    //批量数据插入
    box.insert({
        {"b",1},
        {"e",4},
    });
    print2(box);
    //或者用迭代器范围插入
    box.insert(box.begin(),box.end());
    print2(box);
}   

void test4(){
    map<string,int> box;
    box.insert(pair<string,int>("a",1));
    box.insert({"d",2});
    box.insert(make_pair("c",3));
    print(box);
    //删除数据
    auto it=box.begin();
    ++it;
    box.erase(it);
    print(box);
}

//map中可以根据[key] 获取或修改对应的value值
void test5(){
    map<string,int> box;
    box.insert(pair<string,int>("a",1));
    box.insert({"d",2});
    box.insert(make_pair("c",3));
    box["d"]=4;
    print(box);
    box["a"]=100;
    cout<<box["a"]<<endl;
}

/*
关联式容器针对自定义类型进行处理：
1.自定义类型需要重载operator<()函数
2.函数对象 重载operator()函数 自定义比较器
3.针对std::less做特化处理针对自定义类型处理：和set一样
*/

struct StudentCompare{
    bool operator()(const Student &s1,const Student &s2){
        return s1._id<s2._id;
    }
};

void test6(){
    map<Student,int,StudentCompare> box;
    box.insert({Student(1,"a",18),1});
    box.insert({Student(2,"b",19),2});
    box.insert({Student(3,"c",20),3});
    box.insert({Student(2,"b",19),2});
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


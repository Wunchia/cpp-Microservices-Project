#include <iostream>
#include <map>
#include <utility>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::pair;
using std::string;

/*
 * 使用场景：一般情况适合数据统计使用
 *
 * 举例：
 * 班级里面不同省份的同学有多少个
 * 湖北:5
 * map<string,int>
 * key:省份
 * value:同学个数
 * 
 */

void visitMap(map<string,int>&m){
    for(auto &p:m){
        cout<<p.first<<" = "<<p.second<<endl;
    }
}

void test1(){
    map<string,int> m;
    m.insert({"one",1});
    m.insert({"two",2});
    m.insert({"three",3});
    m.insert({"four",4});
    visitMap(m);
    cout<<"--------------"<<endl;
    //通过下标方式插入 operator[key]添加元素
    m["two"]=2;
    m["five"]=5;
    visitMap(m);
    cout<<"--------------"<<endl;

}

//删除元素erase
void test2(){
    map<string,int> m;
    m.insert({"one",1});
    m.insert({"two",2});
    m.insert({"three",3});
    m.insert({"four",4});
    visitMap(m);
    cout<<"--------------"<<endl;
    auto it=m.begin();
    ++it;
    //参数为迭代器
    m.erase(it);
    visitMap(m);
}

int main(int argc,char *argv[])
{
    // test1(); 
    test2();
    return 0;
}


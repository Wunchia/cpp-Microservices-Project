#include <iostream>
#include <string>
#include <cstring>
#include <stdexcept>
using std::cin;
using std::cout;
using std::endl;
using std::string;

//==================函数模板=========================
template <typename T>
T myMax(T a,T b){
    return (a>b)?a:b;
}

void test1(){
    //隐式实例化
    cout<<myMax(10,20)<<endl;
    cout<<myMax(5.5,3.1)<<endl;

    //隐式推导的常见错误 类型不一致
    // cout<<myMax(10,5.5)<<endl;

    //显式实例化
    //强制将T指定为double，此时10会隐式转换为 double 10.0
    cout<<myMax<double>(10,5.5)<<endl;
}

//通用模板
template <typename T>
int compare(T a,T b){
    if(a<b) return -1;
    if(a>b) return 1;
    return 0;
}

//针对 const char* 的全特化(Full Specialization)
//注意语法：template <>后面跟特化版本
template <>
int compare<const char*>(const char* a,const char* b){
    int res=strcmp(a,b);
    if(res<0) return -1;
    if(res>0) return 1;
    return 0;
}

void test2(){
    int a=10,b=20;
    cout<<compare(a,b)<<endl;

    const char* str1="apple";
    const char* str2="banana";

    //如果不特化，指针比较比的是【内存地址】而不是字符串内容
    //有了特化版本后，会优先调用特化版本
    cout<<compare(str1,str2)<<endl;
}

//=====================类模板==========================
template <typename T,int Size=5>
class StaticArray{
private:
    T m_data[Size];
public:
    void set(int index,const T& value);
    T get(int index)const;
    int getSize() const{return Size;}
};

//在类外实现成员函数时，必须带上模板声明和类名作用域
template <typename T,int Size>
void StaticArray<T,Size>::set(int index,const T& value){
    if(index<0||index>=Size) throw std::out_of_range("Index out of bounds");
    m_data[index]=value;
}

template <typename T,int Size>
T StaticArray<T,Size>::get(int index)const{
    if(index<0||index>=Size) throw std::out_of_range("Index out of bounds");
    return m_data[index];
}

void test3(){
    StaticArray<int,3> intArray;
    intArray.set(0,100);
    cout<<intArray.get(0)<<endl;

    StaticArray<string> strArray;
    strArray.set(4,"C++");
    cout<<strArray.get(4)<<"size:"<<strArray.getSize()<<endl;

}

//--------偏特化---------
//通用类模板
template <typename T,typename U>
class DataPacker{
public:
    void show(){cout<<"通用模板"<<endl;}
};

//偏特化 1：将两个参数指定为相同类型
template <typename T>
class DataPacker<T,T>{
public:
    void show(){cout<<"偏特化：两个参数类型相同"<<endl;}
};

//偏特化 2：将第二个参数固定为指针类型
template <typename T,typename U>
class DataPacker<T,U*>{
public:
    void show(){cout<<"偏特化：第二个参数是指针"<<endl;}
};

void test4(){
    DataPacker<int,double> p1;
    DataPacker<int,int> p2;
    DataPacker<int,char*> p3;

    p1.show();
    p2.show();
    p3.show();
}

//===============注意事项================
//当你在模板内部使用一个依赖于模板参数的内部嵌套类型时，
//编译器无法分辨它是一个静态成员变量还是一个类型
//必须用 typename 声明它是一个类型

template <typename T>
void printContainer(const T& container){
    // T::const_iterator it;//编译器不知道const_iterator是个类型还是个静态变量

    //正确写法：必须加 typename
    typename T::const_iterator it;
    for(it=container.begin();it!=container.end();++it){
        cout<<*it<<" ";
    }
    cout<<endl;
}

int main(int argc,char *argv[])
{
    test1();    
    test2();
    test3();
    test4();
    return 0;
}


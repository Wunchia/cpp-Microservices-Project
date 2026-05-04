#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;


void test1(){
    //string();//无参构造函数，生成一个空字符串""
    string s1;
    cout<<"s1="<<s1<<endl;
    
    //string(const char*rhs);//通过c风格字符串构造一个string对象
    string s2{"hello"};
    cout<<"s2="<<s2<<endl;
    
    //string(const char*rhs,size_type count);
    //通过rhs的前count个字符构造一个string对象
    string s3{"hello",3};
    cout<<"s3="<<s3<<endl;
    cout<<"s3.size="<<s3.size()<<endl;
    cout<<"s3.capacity="<<s3.capacity()<<endl;
    
    //string(const string &rhs); 拷贝构造函数
    string s4{s2};
    cout<<"s4="<<s4<<endl;
    
    //string(const string &rhs.size_t pos,size_t count);
    //通过string的第pos个开始的count个字符构造一个string对象
    string s5{s2,1,3};
    cout<<"s5="<<s5<<endl;
    
    //string(size_type count,char ch);
    //生成一个string对象，该对象包含count个ch
    //注意！！！
    string s6{98,'a'};//这里会用初始化列表，将98理解为ASCII码
    cout<<"s6="<<s6<<endl;
    string s7(97,'a');//这里用小括号，才是用count个ch构造
    cout<<"s7="<<s7<<endl;

    //string(InputIt first,InputIt last);
    //以区间[first,last)“左闭右开区间”构造
    string s8(s7.begin(),s7.begin()+7);
    cout<<"s8="<<s8<<endl;
    cout<<"s8.size="<<s8.size()<<endl;
    cout<<"s8.capacity="<<s8.capacity()<<endl;
}

void test2(){
    string str{"abcdef"};
    //获取首迭代器 指向的是第一个字符的位置
    // auto itBegin=str.begin();
    string::iterator itBegin=str.begin();
    cout<<*itBegin<<endl;
    ++itBegin;
    cout<<*itBegin<<endl;

    auto itEnd=str.end();
    //cout<<*itEnd<<endl;//指向的是最后一个字符的下一个位置
    itEnd--;
    cout<<*itEnd<<endl;
}

//string中常见的操作
void test3(){
    string str{"hello"};
    //元素访问 at(index)
    cout<<str.at(1)<<endl;
    //还可以通过operator[] 下标访问运算符函数 重载的[]
    cout<<str[1]<<endl;
    // front back
    cout<<str.front()<<endl;
    cout<<str.back()<<endl;
    const char*p=str.c_str();
    cout<<p<<endl;
}

int main(int argc,char *argv[])
{
    // test1(); 
    // test2();
    test3();
    return 0;
}


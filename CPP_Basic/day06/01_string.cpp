#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;
/*
 * 常见的字符串操作
 *
 */

void test1(){
    string str{"abcdef"};
    //元素访问
    cout<<str.at(0)<<endl;
    // operator[]
    cout<<str[1]<<endl;
    //通过迭代器访问
    auto it=str.begin();
    it+=2;
    cout<<*it<<endl;

    //容量
    cout<<"size:"<<str.size()<<endl;
    cout<<"capacity:"<<str.capacity()<<endl;
    cout<<"is empty:"<<str.empty()<<endl;
    cout<<"c flavor:"<<str.c_str()<<endl;
}

void test2(){
    string str1{"hello"};
    cout<<str1<<endl;
    string str2{"abc"};
    str1.insert(1,str2);//在1位置插入str2
    cout<<str1<<endl;
    str1.insert(1,"xyz");
    cout<<str1<<endl;
    cout<<"--------->"<<endl;
    str2.push_back('A');
    cout<<str2<<endl;
    string str3{"bbb"};
    str2.append(str3);
    cout<<str2<<endl;
    str2.append(str1.begin(),str1.end());
    cout<<str2<<endl;
}

//删除 erase
void test3(){
    string str1{"abcdef"};
    cout<<str1<<endl;
    auto it1=str1.begin();
    it1+=2;
    //删除迭代器位置的字符
    auto it2=str1.erase(it1);
    cout<<str1<<endl;
    cout<<*it2<<endl;
    cout<<"---------->"<<endl;
    //删除迭代器范围的元素
    auto it3=str1.begin();
    it3+=2;//指向d
    auto it4=str1.erase(it3,str1.end());
    cout<<str1<<endl;
    cout<<*(it4-1)<<endl;
}

//字符串的拼接
void test4(){
    string str1{"abc"};
    string str2{"def"};
    //+
    string str3=str1+str2;
    cout<<str3<<endl;

    string str4=str1+"xyz";
    cout<<str4<<endl;

    string str5=str1+'A';
    cout<<str5<<endl;
}

//字符串的截取
void test5(){
    string str{"abcdef"};
    //substr 区间 左闭右开
    string str2=str.substr(0,3);
    cout<<str2<<endl;

    //从某个位置截取到末尾
    string str3=str.substr(2);
    cout<<str3<<endl;
}

//字符串的查找
void test6(){
    string str{"abcdef"};
    int index=str.find("de");
    if(index<0){
        cout<<"not found"<<endl;
    }else{
        cout<<"index:"<<index<<endl;
    }
}

//字符串的遍历
void test7(){
    string str="abc";
    //for i 循环
    for(int i=0;i<str.size();++i){
        // cout<<str[i]<<endl;
        cout<<str.at(i)<<endl;
    }
    cout<<"----------->"<<endl;
    //foreach增强for循环
    for(char& ch:str){
        cout<<ch<<endl;
    }
    cout<<"---------->"<<endl;
    //迭代器遍历
    auto itBegin=str.begin();
    for(;itBegin!=str.end();++itBegin){
        cout<<*itBegin<<endl;
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


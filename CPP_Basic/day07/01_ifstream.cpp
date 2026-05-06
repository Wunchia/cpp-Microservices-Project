#include <iostream>
#include <fstream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;

//按字符进行读取
void test1(){
    //创建文件输入流对象
    ifstream ifs{"data.txt"};
    //get函数读取字符
    int ch=ifs.get();
    cout<<ch<<endl;
    ch=ifs.get();
    cout<<ch<<endl;
    ch=ifs.get();
    cout<<ch<<endl;
    ch=ifs.get();
    cout<<ch<<endl;
    ch=ifs.get();
    cout<<ch<<endl;
    cout<<"--------->"<<endl;
    cout<<ifs.eof()<<endl;
    ifs.close();
}

//循环读至文件末尾
void test2(){
    //创建文件输入流对象
    ifstream ifs{"data.txt"};
    //get函数读取字符
    int ch;
    while((ch=ifs.get())!=-1){
        cout<<ch<<endl;
    }
    ifs.close();
}

//按字符读取的不同写法
void test3(){
    //创建文件输入流对象
    ifstream ifs{"data.txt"};
    //get函数读取字符
    char ch;
    ifs.get(ch);
    cout<<ch<<endl;
    ifs.close();
}

//按单词读取  利用输入运算符
void test4(){
    //创建文件输入流对象
    ifstream ifs{"data.txt"};
    //输入运算符提取数据
    string word;
    ifs>>word;
    cout<<word<<endl;
    ifs>>word;
    cout<<word<<endl;
    ifs>>word;
    cout<<word<<endl;
    ifs.close();
}

void test5(){
    //创建文件输入流对象
    ifstream ifs{"data.txt"};
    //输入运算符提取数据
    string word;
    while(!ifs.eof()){
        ifs>>word;
        cout<<word<<" ";
    }
    cout<<endl;
    ifs.close();
}

//更常规的做法
void test6(){
    //创建文件输入流对象
    ifstream ifs{"data.txt"};
    //输入运算符提取数据
    string word;
    while(ifs>>word){
        cout<<word<<" ";
    }
    cout<<endl;
    ifs.close();
}

int main(int argc,char *argv[])
{
    // test1(); 
    // test2();
    // test3();
    // test4();
    test5();
    test6();
    return 0;
}


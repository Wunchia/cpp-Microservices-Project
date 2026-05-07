#include <iostream>
#include <fstream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::ofstream;
using std::string;

void test1(){
    ofstream ofs;
    ofs.open("data.txt");

    ofstream ofs2{"data.txt"};

    string fileName="data.txt";
    ofstream ofs3{fileName};
}

/*
 * 写数据到文件的步骤
 * 1.创建输出流对象
 * 2.利用write函数或输出运算符写数据
 * 3.close
 *
 */

void test2(){
    //有参构造
    //如果目标文件不存在 帮我们创建
    //如果目标文件存在 默认打卡模式是out
    //文件内容会被清空
    ofstream ofs{"data2.txt"};
    ofs<<"abc";
    ofs<<123<<" "<<3.14;
    ofs.close();

}

//利用write函数写数据
void test3(){
    ofstream ofs{"data.txt"};//默认方式打卡
    string msg="hello world!";
    ofs.write(msg.c_str(),msg.size());
    ofs.close();
}

//追加的写入
void test4(){
    //默认out---->app
    ofstream ofs{"data.txt",std::ios::app};//追加方式打开
    string msg="abcdef";
    ofs.write(msg.c_str(),msg.size());
    ofs.close();
}

int main(int argc,char *argv[])
{
    // test1();    
    // test2();
    test3();
    test4();
    return 0;
}


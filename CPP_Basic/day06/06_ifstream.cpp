#include <iostream>
#include <fstream>
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;

/*
 * 读取文件数据：
 * 1.创建文件输入流对象
 * 2.利用输入运算符或者函数读取数据
 * 3.close()释放文件资源
 * 
 */

//文件输入流对象的创建
void test1(){
    //无参构造函数创建
    ifstream ifs;
    //通过open函数打开文件，并与之关联
    ifs.open("data.txt");

    //有参构造函数创建
    ifstream ifs2{"data.txt"};//c风格字符串

    std::string fileName="data.txt";
    ifstream ifs3{fileName};//string
}


void test2(){
    ifstream ifs{"data.txt"};
    //通过get函数读取单个字符
    while(!ifs.eof()){
        int i=ifs.get();
        cout<<i<<endl;
    }
}

int main(int argc,char *argv[])
{
    // test1();
    test2();
    return 0;
}


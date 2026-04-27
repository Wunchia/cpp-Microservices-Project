#include <iostream>

using std::cout;//标准输出流
using std::endl;//换行
using std::cin;//标准输入流

void test01(){
    cout<<"hello world"<<endl;

    cout<<"input a num:"<<endl;

    int num;
    //使用cin接收键盘输入
    cin >>num;
    cout<<"num="<<num<<endl;
}

//int argc:命令行参数个数
//argv：具体的命令行参数
int main(int argc,char* argv[])
{
    cout<<argc<<endl;
    test01();
    return 0;
}


#include <iostream>
#include <string>
#include <fstream>
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;

//利用文件输入流实现能够读取一个文件全部的内容
void test(const string& filename ){
    ifstream ifs(filename);
    char ch;
    while((ch=ifs.get())!=-1){
        cout<<ch;
    }
}

int main(int argc,char *argv[])
{
    test("data.txt");
    return 0;
}


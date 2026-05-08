#include <iostream>
#include <string>
#include <sstream>
#include <limits>
using std::string;
using std::cin;
using std::cout;
using std::endl;

int getValidInt(const string& prompt){
    string input;
    int result;

    while(true){
        cout<<prompt;
        if(!std::getline(cin,input)){
            exit(0);
        }
        std::stringstream ss(input);

        if(ss>>result&&(ss>>std::ws).eof()){
            return result;
        }
        cout<<"输入错误"<<endl;
    }
}

int main(int argc,char *argv[])
{
    int val=getValidInt("请输入一个整数：");
    cout<<"你输入的数字："<<val<<endl;
    return 0;
}


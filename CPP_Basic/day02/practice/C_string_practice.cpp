#include <iostream>
#include <cstring>
using std::cin;
using std::cout;
using std::endl;

int main(int argc,char *argv[])
{
    const char*s1="Hello, ";
    const char*s2="World!";

    char *res=new char[strlen(s1)+strlen(s2)+1];

    strcpy(res,s1);
    strcat(res,s2);

    cout<<"拼接后的字符串："<<res<<endl;

    delete[](res);
    
    return 0;
}


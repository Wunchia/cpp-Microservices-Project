#include <iostream>
#include <fstream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;

void test_file_pointer(){
    std::ifstream ifs{"test.txt"};
    ifs.seekg(0,std::ios::end);
    long length=ifs.tellg();
    cout<<"file size: "<<length<<"bytes"<<endl;

    ifs.seekg(length/2,std::ios::beg);
    string remain;
    cout<<"from middle: ";
    while(ifs>>remain){
        cout<<remain<<" ";
    }
    cout<<endl;
    ifs.close();
}

int main(int argc,char *argv[])
{
    test_file_pointer();
    return 0;
}


#include <iostream>
#include <string>
#include <fstream>
using std::cin;
using std::cout;
using std::endl;

void testFileRead(){
    std::ifstream ifs("test.txt");
    if(!ifs.is_open()){
        return;
    }
    std::string word;
    std::string line;
    char ch;

    // while(ifs.get(ch)){
    //     cout<<ch;
    // }

    // while(ifs>>word){
    //     cout<< "word:"<<word<<endl;
    // }

    while(getline(ifs,line)){
        cout<<"Line:"<<line<<endl;
    }

    ifs.close();
}

int main(int argc,char *argv[])
{
    testFileRead();
    return 0;
}


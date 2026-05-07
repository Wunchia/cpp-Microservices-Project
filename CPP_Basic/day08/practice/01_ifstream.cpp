#include <iostream>
#include <fstream>
#include <string>
using std::cin;
using std::cout;
using std::endl;

void test_ifstream(){
    std::ifstream ifs("test.txt");
    if(!ifs.is_open()){
        std::cerr<<"Open file failed!"<<endl;
        return;
    }
    //按字符读取
    char ch;
    while(ifs.get(ch)){
        cout<<ch;
    }
    ifs.clear();
    ifs.seekg(0);
    cout<<">>-----------------<<"<<endl;
    //按单词读取
    std::string word;
    while(ifs>>word){
        cout<<word<<"->";
    }
    cout<<endl;
    ifs.clear();
    ifs.seekg(0);
    cout<<">------------------<"<<endl;
    //按行读取
    std::string line;
    while(std::getline(ifs,line)){
        cout<<line<<endl;
    }
    ifs.close();
}


int main(int argc,char *argv[])
{
    test_ifstream(); 
    return 0;
}


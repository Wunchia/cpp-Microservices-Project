#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using std::string;
using std::vector;
using std::ifstream;
using std::cin;
using std::cout;
using std::endl;

void read_all(const string&filename){
    ifstream ifs{filename,std::ios::binary|std::ios::ate};
    if(!ifs){
        std::cerr<<"open file failed"<<endl;
        return;
    }

    std::streamsize size=ifs.tellg();

    ifs.seekg(0,std::ios::beg);

    vector<char> buffer(size);

    if(ifs.read(buffer.data(),size)){
        string content(buffer.data(),size);
        cout<<"file content size:[ "<<size<<" ] bytes."<<endl;
        cout<<"content preview:\n"<<content<<endl;
    }
    ifs.close();
}

int main(int argc,char *argv[])
{
    read_all("test.txt");    
    return 0;
}


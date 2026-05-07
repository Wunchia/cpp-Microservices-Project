#include <iostream>
#include <fstream>
using std::cin;
using std::cout;
using std::endl;

void test_ofstream(){
    std::ofstream ofs{"output.txt",std::ios::app};
    if(ofs.good()){
        ofs<<"hello c++ IO"<<endl;
        ofs<<"line2: system programming."<<endl;
    }
    ofs.close();
}

int main(int argc,char *argv[])
{
    test_ofstream();    
    return 0;
}


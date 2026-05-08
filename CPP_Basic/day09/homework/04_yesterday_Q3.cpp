#include <iostream>
#include <fstream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;
void read_by_word(const string & filename){
    ifstream ifs{filename};
    if(!ifs) return;
    string word;
    while(ifs>>word){
        cout<<word<<" ";
    }
    cout<<endl;
    ifs.close();
}

void read_by_line(const string & filename){
    ifstream ifs(filename);
    if(!ifs) return;
    string line;
    while(getline(ifs,line)){
        cout<<line<<endl;
    }
    ifs.close();
}

int main(int argc,char *argv[])
{
    read_by_word("test.txt");
    read_by_line("test.txt");
    return 0;
}


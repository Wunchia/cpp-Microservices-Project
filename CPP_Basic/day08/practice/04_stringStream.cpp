#include <iostream>
#include <sstream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;

void test_istringstream(){
    string content="192.168.1.1 8080 server_name";
    std::istringstream iss(content);

    string ip,port,name;
    if(iss>>ip>>port>>name){
        cout<<"IP: "<<ip<<", Port: "<<port<<", server: "<<name<<endl;
    }
}

int main(int argc,char *argv[])
{
    test_istringstream();    
    return 0;
}


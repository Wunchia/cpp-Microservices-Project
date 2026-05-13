#include <iostream>
#include <map>
#include <string>
#include <utility>
using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::pair;

void visitMap(map<int,string> m){
    for(auto &p:m){
        cout<<p.first<< " "<<p.second<<" | ";
    }
    cout<<endl;
}

int main(int argc,char *argv[])
{
    map<int,string> m{
        {1,"Alice"},
        {2,"Bruce"},
        {3,"Cealsa"}
    };    
    visitMap(m);
    cout<<"----1-----"<<endl;
    cout<<m[1]<<endl;
    cout<<"----------"<<endl;
    m[2]="Blue";
    visitMap(m);
    m[4]="Daisy";
    visitMap(m);
    return 0;
}



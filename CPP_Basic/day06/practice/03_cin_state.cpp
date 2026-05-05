#include <iostream>
#include <limits>
using std::cin;
using std::cout;
using std::endl;

void testCinState(){
    int num;
    cout<<"input a num:"<<endl;

    while(cin>>num){
        cout<<"recived correct num:"<<num<<endl;
    }

    if(cin.fail()){
        cout<<"illigal input, stream is in the fail state"<<endl;
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
}

int main(int argc,char *argv[])
{
    testCinState(); 
    return 0;
}


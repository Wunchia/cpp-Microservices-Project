#include <iostream>
#include <unistd.h>
using std::cin;
using std::cout;
using std::endl;

void testCoutBuffer(){
    cout<<"Hello buffer";
    sleep(3);
    cout<<endl;

    cout<<"hello buffer again";
    sleep(3);
    cout<<std::flush;
}

int main(int argc,char *argv[])
{
    testCoutBuffer(); 
    return 0;
}


#include <iostream>
#include "Mylogger.hh"

using std::cin;
using std::cout;
using std::endl;

void testInfo(){
    LogInfo("in local scope"); 
}

int main(int argc,char *argv[])
{
    LogDebug("system success up");    
    LogWarn("test Warning");
    testInfo();
    LogError("test Error");    
    MyLogger::destroyInstance();
    return 0;
}


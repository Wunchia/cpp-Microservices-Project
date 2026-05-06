#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;

class Logger{
public:
    static Logger* getInstance(){
        if(!ms_instance){
            ms_instance=new Logger();
        }
        return ms_instance;
    }

    static void log(const string& log ){
        cout<<log<<endl;
    }

    static void destroyInstance(){
        if(ms_instance){
            delete ms_instance;
            ms_instance=nullptr;
        }
    }

private:
    Logger(){}
    Logger(const Logger& rhs)=delete;
    Logger&operator=(const Logger&rhs)=delete;
    ~Logger(){}
    static Logger* ms_instance;
};

Logger* Logger::ms_instance=nullptr;

int main(int argc,char *argv[])
{
    Logger* g_log=Logger::getInstance();
    Logger* d_log=Logger::getInstance();

    cout<<g_log<<endl;
    cout<<d_log<<endl;

    Logger::destroyInstance();
    g_log=nullptr;
    d_log=nullptr;

    Logger::log("test log");

    return 0;
}


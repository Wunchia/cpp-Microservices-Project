#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
using std::vector;
using std::string;
using std::ifstream;
using std::cin;
using std::cout;
using std::endl;

class PersonInfo{
public:
    PersonInfo()=default;

    void setName(string &name){
        m_name=name;
    }

    void setPhones(vector<string>&phones){
        m_phones=phones;
    }

    void print()const{
        cout<<m_name<<": ";
        for(const auto&phone:m_phones){
            cout<<phone<<" ";
        }
        cout<<endl;
    }

private:
    string m_name;
    vector<string> m_phones;
};

void processPhoneFile(const string&filename){
    ifstream ifs{filename};
    if(!ifs){
        std::cerr<<"open file failed"<<endl;
        return;
    }

    vector<PersonInfo> personInfos;
    string line;

    while(std::getline(ifs,line)){
        if(line.empty()) continue;
        
        std::stringstream ss(line);
        string name;
        string phone;
        vector<string> phones;
        //处理这一行的信息 新建personInfo类 向vector内添加
        if(ss>>name){
            while(ss>>phone){
                phones.push_back(phone);
            }
            PersonInfo info;
            info.setName(name);
            info.setPhones(phones);
            personInfos.push_back(info);
        }
    }

    cout<<"----contactors----"<<endl;
    for(const auto& person:personInfos){
        person.print();
    }
}

int main(int argc,char *argv[])
{
    processPhoneFile("phone.txt");    
    return 0;
}


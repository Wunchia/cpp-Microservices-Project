#include <iostream>
#include <string.h>
#include <vector>
#include <nlohmann/json.hpp>

using namespace std;
using json=nlohmann::json;

struct Student{
    int id;
    string name;
    int chinese;
    int math;
    int english;
    vector<string> hobbies;
    bool isGraduated;
};

//Student -> JSON
void to_json(json& j,const Student& s){
    j=json{
        {"id",s.id},
        {"name",s.name},
        {"scores",{
            {"chinese",s.chinese},
            {"math",s.math},
            {"english",s.english}
        }},
        {"hobbies",s.hobbies},
        {"isGraduated",s.isGraduated},
    };
}

//JSON -> Student
void from_json(const json& j,Student& s){
    j.at("id").get_to(s.id);
    j.at("name").get_to(s.name);
    j.at("scores").at("chinese").get_to(s.chinese);
    j.at("scores").at("math").get_to(s.math);
    j.at("scores").at("english").get_to(s.english);
    j.at("hobbies").get_to(s.hobbies);
    j.at("isGraduated").get_to(s.isGraduated);
}

int main(int argc,char *argv[])
{
    Student s={1001,"花生",92,95,88,{"唱歌","跳舞","rap","篮球"},false};

    //序列化
    json j=s;
    string json_str=j.dump(4);
    cout<<json_str<<endl;

    //反序列化
    Student s2=j.get<Student>();
    cout<<"反序列化：id="<<s2.id<<", name="<<s2.name<<endl;

    return 0;
}

#include <iostream>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

class Student{
public:
    Student(const string& name,int id,double score)
    :_name(name)
    ,_id(id)
    ,_score(score)
    {}

    void print()const{
        cout<<">---Student Info---<"<<endl;
        cout<<"name: "<<_name<<endl;
        cout<<"id: "<<_id<<endl;
        cout<<"score: "<<_score<<endl;
        cout<<">------------------<"<<endl;
    }
private:
    string _name;
    int _id;
    double _score;
};

void traverseStudent1(const vector<Student>& s){
    for(auto &it:s){
        it.print();
    }
}

void traverseStudent2(const vector<Student>& s){
    for(auto it=s.begin();it!=s.end();++it){
        it->print();
    }
}

int main(int argc,char *argv[])
{
    vector<Student> students
    {{"Alice",1001,98.5},
     {"Bruce",1002,89.6},
     {"Ceasle",1003,67.8}};
     
    traverseStudent1(students);
    cout<<">>>>-------<<<<"<<endl;
    traverseStudent2(students);
    
    students.push_back({"Daicy",1004,87.5});
    cout<<"=====after push_back======"<<endl;

    traverseStudent1(students);
    cout<<">>>>-------<<<<"<<endl;
    traverseStudent2(students);

    return 0;
}


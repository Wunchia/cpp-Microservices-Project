#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;

class Student{
public:
    Student(string name,int id,double score)
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

int main(int argc,char *argv[])
{
    Student s1{"Jack",1001,89.6};
    Student s2{"Alice",1002,96.5};
    s1.print();
    s2.print();
    return 0;
}


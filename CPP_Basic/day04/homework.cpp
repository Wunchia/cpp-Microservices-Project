#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;

class Student{
private:
    std::string _name;
    int _id;
    int _age;
public:
    Student(std::string name,int id,int age)
    :_name(name),_id(id),_age(age)
    {
        cout<<"constructed:"<<_name<<endl;
    }

    void print(){
        cout<<"id:"<<_id<<endl<<"name:"<<_name<<endl<<"age:"<<_age<<endl<<"----"<<endl;
    }
    ~Student(){
        cout<<"destructed:"<<_name<<endl;
    }
};

int main(int argc,char *argv[])
{
    Student s1("zs",1001,21);
    Student s2("ls",1002,23);
    Student s3("ww",1003,27);
    s1.print();
    s2.print();
    s3.print();
    return 0;
}
#include <iostream>
#include <cstring>
using std::cin;
using std::cout;
using std::endl;
//定义类Person，包含姓名（char*）、年龄，
//提供成员函数 display输出信息。
//类Employee由Person派生，包含部门（char*）、工资, 
//成员函数display用来输出职工姓名、年龄、部门、工资。
//要求Employee对象能够进行正确的复制、赋值操作，同时提供计算平均工资的功能。

class Person{
public:
    Person(char* name,int age)
    :_name(new char[strlen(name)+1]{})
    ,_age(age)
    {
        strcpy(_name,name);
    }

    Person(const Person&rhs)
    :_name(new char[strlen(rhs._name)+1]{})
    ,_age(rhs._age)
    {
        strcpy(_name,rhs._name);
    }

    Person& operator=(const Person&rhs){
        if(this!=&rhs){
            char* tmp=new char[strlen(rhs._name)+1]{};
            strcpy(tmp,rhs._name);
            delete[]_name;
            _name=tmp;
            _age=rhs._age;
        }
        return *this;
    }

    virtual ~Person(){
        if(_name){
            delete[]_name;
            _name=nullptr;
        }
    }
    virtual void display()const{
        cout<<"name:"<<_name<<" age:"<<_age<<endl;
    }
private:
    char* _name;
    int _age;
};

class Employee : public Person
{
public:
    Employee(const Person &p,char* dept,double salary)
    :Person(p)
    ,_dept(new char[strlen(dept)+1]{})
    ,_salary(salary)
    {
        strcpy(_dept,dept);
        total_salary+=_salary;
    }

    Employee(const Employee&rhs)
    :Person(rhs)
    ,_dept(new char[strlen(rhs._dept)+1]{})
    ,_salary(rhs._salary)
    {
        strcpy(_dept,rhs._dept);
        ++member_count;
        total_salary+=_salary;
    }

    Employee&operator=(const Employee&rhs){
        if(this!=&rhs){
            Person::operator=(rhs);
            char* tmp=new char[strlen(rhs._dept)+1]{};
            strcpy(tmp,rhs._dept);
            delete[]_dept;
            _dept=tmp;
            total_salary-=_salary;
            _salary=rhs._salary;
            total_salary+=_salary;
        }
        return *this;
    }

    virtual ~Employee(){
        if(_dept){
            delete[] _dept;
        }
        total_salary-=_salary;
    }

    virtual void display()const override{
        cout<<"-------------"<<endl;
        Person::display();
        cout<<"dept:"<<_dept<<" salary:"<<_salary<<endl;
    }

    static void getAvg_Salary(){
        cout<<"======================"<<endl;
        cout<<"avg_salary:"<<(total_salary/member_count)<<endl;
        cout<<"======================"<<endl;
    }

private:
    char* _dept;
    double _salary;
    static double total_salary;
    static int member_count;
};

double Employee::total_salary=0;
int Employee::member_count=0;

void test(){
    Person xly{"xly",18};
    Person zqd{"zqd",18};
    Person lws{"lws",18};
    Person lw{"lw",18};
    Person zyt{"zyt",18};
    
    Employee e_xly{xly,"ByteDance",28000};
    Employee e_zqd{zqd,"Tencent",28000};
    Employee e_lws{lws,"OpenAI",48000};
    Employee e_lw{lw,"Alibaba",28000};
    Employee e_zyt{zyt,"Google",48000};
    e_xly.display();
    e_zqd.display();
    e_lws.display();
    e_lw.display();
    e_zyt.display();
    Employee::getAvg_Salary();
}

int main(int argc,char *argv[])
{
    test(); 
    return 0;
}


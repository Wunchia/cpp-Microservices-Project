#include <iostream>
#include <string>
#include <list>
using namespace std;

class Student{
public:
    Student(string name,int Chinese,int Math,int English)
    :_name(name)
    ,_Chinese(Chinese)
    ,_Math(Math)
    ,_English(English)
    ,_Sum(Chinese+Math+English)
    {}

    string _name;
    int _Chinese;
    int _Math;
    int _English;
    int _Sum;

};

bool compareStudent(const Student& s1,const Student& s2){
    if(s1._Sum==s2._Sum){
        if(s1._Chinese==s2._Chinese){
            return s1._Math>s2._Math;
        }
        return s1._Chinese>s2._Chinese;
    }
    return s1._Sum>s2._Sum;
}

void printList(const list<Student>& l){
    cout<<"姓名\t语文\t数学\t英语\t总成绩"<<endl;
    for(const auto& e:l){
        cout<<e._name<<"\t"
        <<e._Chinese<<"\t"
        <<e._Math<<"\t"
        <<e._English<<"\t"
        <<e._Sum<<endl;
    }
}

int main(int argc,char *argv[])
{
    list<Student> L;
    
    L.push_back(Student("张三",90,80,70));
    L.push_back(Student("李四",80,80,80));
    L.push_back(Student("王五",90,80,90));
    L.push_back(Student("赵六",80,70,90));
    L.push_back(Student("孙七",95,85,90));

    cout<<"=====before sort======"<<endl;
    printList(L);
    L.sort(compareStudent);
    cout<<"=====after sort======"<<endl;
    printList(L);

    return 0;
}


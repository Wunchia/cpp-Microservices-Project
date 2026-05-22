#include <iostream>
#include <string>
#include <set>
using std::set;
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::ostream;


template <typename Container>
void print(Container& box){
    for(auto & e:box){
        cout<<" "<<e;
    }
    cout<<endl;
}

/*
关联式容器针对自定义类型进行处理：
1.自定义类型需要重载operator<()函数
2.函数对象 重载operator()函数 自定义比较器
3.针对std::less做特化处理
*/

class Student{
public:
    Student(int id,string name,int age):
        _id(id),_name(name),_age(age){}

    friend ostream& operator<<(ostream &os,const Student &s){
        os<<"_id:"<<s._id<<" _name:"<<s._name<<" _age:"<<s._age<<endl;
        return os;
    }

    bool operator<(const Student& other)const{
        return this->_id<other._id;
    }

private:
    int _id;
    string _name;
    int _age;
};

void test1(){
    set<Student> box1;
    box1.insert(Student(1,"张三",18));
    box1.insert(Student(1,"赵六",21));
    box1.insert(Student(2,"李四",20));
    box1.insert(Student(3,"王五",19));
    print(box1);
}

int main(int argc,char *argv[])
{
    test1();    
    return 0;
}


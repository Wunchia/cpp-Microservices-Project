#include <iostream>
#include <string>
#include <set>
using std::cin;
using std::cout;
using std::endl;
using std::ostream;
using std::set;
using std::string;

template <typename Container>
void print(Container &box)
{
    for (auto &e : box)
    {
        cout << " " << e;
    }
    cout << endl;
}

/*
关联式容器针对自定义类型进行处理：
1.自定义类型需要重载operator<()函数
2.函数对象 重载operator()函数 自定义比较器
3.针对std::less做特化处理
*/

class Student
{
public:
    Student(int id, string name, int age) : _id(id), _name(name), _age(age) {}

    friend ostream &operator<<(ostream &os, const Student &s)
    {
        os << "_id:" << s._id << " _name:" << s._name << " _age:" << s._age << endl;
        return os;
    }

    int _id;
    string _name;
    int _age;
};

// 方式二：自定义一个比较器 --> 函数对象
struct StudentCompare
{
    // operator()
    bool operator()(const Student &lhs, const Student &rhs) const
    {
        return lhs._age < rhs._age;
    }
};

// 方式三：针对std::less做特化处理
//什么时候采用特化处理？
//通用模板存在，且通用模板不匹配的时候，使用模板特化处理
namespace std
{
    template <>
    struct less<Student>
    {
        bool operator()(const Student &lhs, const Student &rhs) const
        {
            return lhs._age < rhs._age;
        }
    };
}

void test1()
{
    set<Student> box1;//这里compare用的还是默认值 std::less
    //通用模板不能处理Student类型，才使用特化
    box1.insert(Student(1, "张三", 18));
    box1.insert(Student(1, "赵六", 21));
    box1.insert(Student(2, "李四", 20));
    box1.insert(Student(3, "王五", 19));
    print(box1);
}

int main(int argc, char *argv[])
{
    test1();
    return 0;
}

#include <iostream>
#include <string.h>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;

/* 
 * 
 * 调用移动构造 
 * 
 */

class String
{
public:
    // default no arg constructor
    String()
    /* : _pstr(nullptr) */
    : m_pstr(new char[1]())
    {
        cout << "String()" << endl;
    }

	// args constructor
    String(const char *pstr)
    : m_pstr(new char[strlen(pstr) + 1]())
    {
        cout << "String(const char *)" << endl;
        strcpy(m_pstr, pstr);
    }

	// copy constructor
    String(const String & rhs)
    : m_pstr(new char[strlen(rhs.m_pstr) + 1]())
    {
        cout << "String(const String &)" << endl;
        strcpy(m_pstr, rhs.m_pstr);
    }

	// operator =
    String & operator=(const String & rhs)
    {
        cout << "String &operator=(const String &)" << endl;
        if(this != &rhs)
        {
            if(m_pstr)
            {
                delete [] m_pstr;
            }
            m_pstr = new char[strlen(rhs.m_pstr) + 1]();
            strcpy(m_pstr, rhs.m_pstr);
        }
        return *this;
    }

	// length
    size_t length() const
    {
        size_t len = 0;
        if(m_pstr)
        {
            len = strlen(m_pstr);
        }

        return len;

    }

	// c style string
    const char * c_str() const
    {
        if(m_pstr)
        {
            return m_pstr;
        }
        else
        {
            return nullptr;
        }
    }

	// destructor
    ~String()
    {
        cout << "~String()" << endl;
        if(m_pstr)
        {
            delete [] m_pstr;
            m_pstr = nullptr;
        }
    }

    void print() const
    {
        if(m_pstr)
        {
            cout << "m_pstr = " << m_pstr << endl;
        }else{
            cout << endl;
        }
    }

    //move constructor
    String(String && rhs)//只处理右值 右值引用绑定临时对象
    :m_pstr(rhs.m_pstr)//浅拷贝
    {
        cout<<"move constructor"<<endl;
        //把临时对象的指针设置为空
        rhs.m_pstr=nullptr;
    }

    //移动赋值运算符函数
    String& operator=(String &&rhs)//右值引用绑定临时对象
    {
        //自赋值判断
        if(this!=&rhs){
            //回收原本的空间
            delete [] m_pstr;
            //深拷贝 ---> 浅拷贝
            m_pstr=rhs.m_pstr;
            //将临时对象的指针置空
            rhs.m_pstr=nullptr;
        }
        cout << "move assignment" << endl;
        return *this;
    }

private:
    char * m_pstr;
};

void func1(String str){
    str.print();
}

void func2(String str){
    str.print();
}

String func3(){
    String s{"abc"};
    return s;
}

String str{"aaa"};
String func4(){
    return str;
}

//测试对象作为参数
void test1(){
    String s{"abc"};
    // func1(s);  //调用拷贝构造  
    func2(std::move(s)); //调用移动构造
}

//测试对象作为返回值
void test2(){
    // func3();
    func4();
}

int main(int argc,char *argv[])
{
    // test1();    
    test2();
    return 0;
}


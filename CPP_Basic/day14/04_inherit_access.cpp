#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class Father1{
public:
    int m_data1;
protected:
    int m_data2;
private:
    int m_data3;
};

class Son1 : public Father1{
public:
    void func(){
        m_data1;
        m_data2;
        // m_data3;
    }
};


class Father2{
public:
    int m_data1;
protected:
    int m_data2;
private:
    int m_data3;
};

class son2:protected Father2{
public:
    void func(){
        m_data1;
        m_data2;
        // m_data3;
    }
};

class Father3{
public:
    int m_data1;
protected:
    int m_data2;
private:
    int m_data3;
};

class son3:private Father3{
public:
    void func(){
        m_data1;
        m_data2;
        // m_data3;
    }
};

int main(int argc,char *argv[])
{
    
    return 0;
}


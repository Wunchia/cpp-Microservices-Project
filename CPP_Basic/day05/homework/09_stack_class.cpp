#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;

class Stack{
public:
    explicit Stack(size_t limit)
    :max_limit(limit)
    {
        m_stack.reserve(limit);
    }

    bool empty()const{
        return m_stack.empty();
    }

    bool full()const{
        return m_stack.size()>=max_limit;
    }
    void push(int num){
        if(full()){
            return;
        }
        m_stack.push_back(num);
    }

    void pop(){
        if(empty()){
            return;
        }
        m_stack.pop_back();
    }

    const int& top()const{
        if(empty()){
            throw std::out_of_range("stack is empty");
        }
        return m_stack.back();
    }
private:
    vector<int> m_stack;
    size_t max_limit;
};

void test1(){
    Stack s1(10);
    if(s1.empty()){
        cout<<"s1 is empty"<<endl;
    }
    int i=0;
    while(!s1.full()){
        s1.push(i++);
    }

    if(s1.full()){
        cout<<"s1 is full"<<endl;
    }
    while(!s1.empty()){
        cout<<s1.top()<<endl;
        s1.pop();
    }
}

int main(int argc,char *argv[])
{
    test1();
    return 0;
}


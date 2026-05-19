#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
using std::cin;
using std::cout;
using std::endl;
using std::vector;

template <typename T>
class Stack{
private:
    vector<T> elements;

public:
    //入栈
    void push(const T& element){
        elements.push_back(element);
    }

    //入栈（右值引用，优化移动语义）
    void push(T&& element){
        elements.push_back(std::move(element));
    }

    //出栈
    void pop(){
        if(elements.empty()){
            throw std::underflow_error("Stack<>::pop():尝试对空栈进行pop操作");
        }
        elements.pop_back();
    }

    //查看栈顶元素（可修改）
    T& top(){
        if (elements.empty()){
            throw std::underflow_error("Stack<>::top():尝试访问空栈的栈顶");
        }
        return elements.back();
    }

    //查看栈顶元素（常量版本）
    const T& top() const{
        if(elements.empty()){
            throw std::underflow_error("Stack<>::top():尝试访问空栈的栈顶");
        }
        return elements.back();
    }

    bool empty()const{
        return elements.empty();
    }

    size_t size()const{
        return elements.size();
    }
};

struct Point{
    int x;
    int y;

    friend std::ostream& operator<<(std::ostream &os,const Point &p){
        os<<"("<<p.x<<", "<<p.y<<")";
        return os;
    }
};

int main(int argc,char *argv[])
{
    // ==========================================
    // 测试 1：基本数据类型 (int)
    // ==========================================
    std::cout << "--- 测试 1: 整型栈 (Stack<int>) ---" << std::endl;
    Stack<int> intStack;
    
    intStack.push(10);
    intStack.push(20);
    intStack.push(30);
    
    std::cout << "当前栈大小: " << intStack.size() << std::endl;
    while (!intStack.empty()) {
        std::cout << "栈顶元素: " << intStack.top() << std::endl;
        intStack.pop();
    }
    std::cout << std::endl;

    // ==========================================
    // 测试 2：类类型 (std::string)
    // ==========================================
    std::cout << "--- 测试 2: 字符串栈 (Stack<std::string>) ---" << std::endl;
    Stack<std::string> stringStack;
    
    stringStack.push("Hello");
    stringStack.push("Template");
    stringStack.push("C++");
    
    // 修改栈顶元素测试
    stringStack.top() = "Modern C++"; 
    
    while (!stringStack.empty()) {
        std::cout << "弹出栈顶: " << stringStack.top() << std::endl;
        stringStack.pop();
    }
    std::cout << std::endl;

    // ==========================================
    // 测试 3：自定义结构体 (Point)
    // ==========================================
    std::cout << "--- 测试 3: 自定义结构体栈 (Stack<Point>) ---" << std::endl;
    Stack<Point> pointStack;
    
    pointStack.push({1, 2});
    pointStack.push({3, 4});
    pointStack.push({5, 6});
    
    while (!pointStack.empty()) {
        cout << "坐标栈顶: " << pointStack.top() << endl;
        pointStack.pop();
    }
    cout << endl;

    // ==========================================
    // 测试 4：异常处理 (边界测试)
    // ==========================================
    std::cout << "--- 测试 4: 异常边界测试 ---" << std::endl;
    Stack<double> emptyStack;
    try {
        std::cout << "尝试对空栈进行 pop..." << std::endl;
        emptyStack.pop();
    } catch (const std::underflow_error& e) {
        std::cout << "捕获到标准异常: " << e.what() << std::endl;
    }
    return 0;
}


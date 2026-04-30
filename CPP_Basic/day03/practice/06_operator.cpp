#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class HeapData{
public:
    HeapData(int val)
    :_data(new int(val)){}

    ~HeapData(){delete _data;}

    HeapData& operator=(const HeapData& rhs){
        cout<<"调用赋值运算符"<<endl;

        if(this==&rhs) return *this;

        delete _data;

        _data=new int(*rhs._data);

        return *this;
    }

    void print(){
        cout<<*_data<<endl;
    }

private:
    int *_data;
};

void test(){
    HeapData H1{10};
    HeapData H2{20};
    H1.print();
    H2.print();
    H2=H1;
    H1.print();
    H2.print();
}

int main(int argc,char *argv[])
{
    test();   
    return 0;
}


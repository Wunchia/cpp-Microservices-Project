#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class Point{
public:
    void print(){
        cout<<"Point context"<<endl;
    }
};

void test1(){
    Point arr[3];
    for(int i=0;i<3;i++){
        arr[i].print();
    }

    Point* ptr=new Point[2];
    for(int i=0;i<2;++i){
        (ptr+i)->print();
    }
    delete[] ptr;
}

int main(int argc,char *argv[])
{
    test1();
    return 0;
}


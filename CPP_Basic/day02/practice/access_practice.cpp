#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class TestAccess{
public:
    int public_val;
    void show(){
        cout<<private_val<<endl;
    }
private:
    int private_val=10;
};

int main(int argc,char *argv[])
{
    TestAccess obj;
    obj.public_val=10;
    // obj.private_val;
    obj.show();
    return 0;
}


#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int foo(int x, int y)
{
    if (x <= 0 || y <= 0)
        return 1;
    return 3 * foo(x - 1, y / 2);
}

int main(int argc, char *argv[])
{
    cout << foo(3, 5) << endl;
    return 0;
}

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*

*/
typedef int(*func_ptr1)(int,int);

int test01(int a, int b) {
    return a + b;
}

int test02(int a, int b, int ptr(int, int)) {
    return ptr(a, b);
}

int main(void) {
    func_ptr1 ptr1 = test01;
    int (*ptr2)(int, int, func_ptr1)=test02;
    int res = (*ptr2)(2, 3, ptr1);
    printf("%d\n", res);

    return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*
在main函数中定义两个局部变量：
int a = 10;
int b = 20;
请实现以下两个函数，用于完成局部变量a和b的交换：
void swap(int *pa, int *pb);
void swap2(int **pa, int **pb);
这两个函数都应该可以实现交换a和b的值。
*/

void swap(int* pa, int* pb) {
    int temp = *pa;
    *pa = *pb;
    *pb = temp;
}

void swap2(int** pa, int** pb) {
    int temp = **pa;
    **pa = **pb;
    **pb = temp;
}


int main(void) {
    int a = 10;
    int b = 20;
    printf("a=%d ,b=%d\n", a, b);
    swap(&a, &b);
    printf("a=%d ,b=%d\n", a, b);
    int* pa = &a;
    int* pb = &b;
    swap2(& pa, & pb);
    printf("a=%d ,b=%d\n", a, b);

    return 0;
}
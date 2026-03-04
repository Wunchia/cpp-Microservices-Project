#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*

*/

int main(void) {
    int a[3][3] = { { 1,2,3 }, { 4, 5, 6 },{7,8,9} };//a是一个数组名 const pointer
    int* p1 = a;//p指向a，即指向a首元素{1，2，3}的首地址，p的步长是一个整型的大小，a的步长是一个一维数组的大小（隐式类型转换，int (*)[3]→int *）
    printf("*a=%d\n", *a);//解引用得到的是{1,2,3}这个一维数组的数组名，本质上是{1,2,3}首元素（1）的地址
    printf("*p=%d\n", *p1++);//解引用得到1的值
    printf("**a=%d\n", **a);//再解引用得到{1,2,3}的首元素（1）的值
    //printf("%d", **p1);//将a的首元素的值（1）当作地址解引用，指向一个未定义的区域
    //因为发生了隐式类型转换，所以a需要**才能得到的值，通过p只需要*就能得到

    printf("==================\n");

    int* p2 = &a;//p指向a，即指向a首元素{1，2，3}的首地址，p的步长是一个整型的大小，&a的步长是一个二维数组的大小（隐式类型转换，int (*)[3][3]→int *）
    printf("*a=%d\n", *a);//解引用得到的是{1,2,3}这个一维数组的数组名，本质上是{1,2,3}首元素的地址
    printf("*p=%d\n", *p1);//解引用得到a的首元素的值
    printf("**a=%d\n", **a);//再解引用得到{1,2,3}的首元素的值
    //printf("%d", **p1);//将a的首元素的值（1）当作地址解引用，指向一个未定义的区域
    
    printf("==================\n");
    char fruits[3][10] = { "apple","banana","cherry"};
    char* p3 = fruits;
    printf("%c\n", fruits);
    printf("%s\n", *fruits);
    printf("%c\n", **fruits);
    printf("%c\n", p3);
    printf("%c\n", *p3);
    //printf("%c\n", **p3);


    return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
/*

*/
//int global_num = 666;//÷ÿ∏¥∂®“Â
//int global_num;

void test01() {
    int a = 12345;
    printf("test01--------before.\n");
    printf("%d\n", EXIT_SUCCESS);//0
    printf("%d\n", EXIT_FAILURE);//1
    //exit(EXIT_FAILURE);
    printf("test01-------after.\n");
}

int* test02() {
    int a = 10086;
    printf("test02 did\n");
    return &a;
}

void test03() {
    printf("test_global_in_main did\n");
    printf("global_num = %d in main.c\n", global_num);
}

int main(void) {
    //test01();
    //int* p = test02();
    //printf("%d\n", *p);
    //test01();
    //printf("before p\n");
    //printf("%d\n", *p);
    //printf("after p\n");
    /*test03();
    test_global_in_test();*/

    return 0;
}
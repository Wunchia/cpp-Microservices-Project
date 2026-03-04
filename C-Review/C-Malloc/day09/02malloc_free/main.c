#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
/*

*/

void test01() {
    int len = 80;
    int* arr = malloc(len * sizeof(int));//这里其实发生了隐式类型转换，void*-->int*
    if (arr == NULL) {
        printf("malloc failed.\n");
        return;
    }
    for (int i = 0; i < len; i++) {
        arr[i] = i;
    }
    for (int i = 0; i < 80; i++) {
        printf("%d\n", arr[i]);
    }
    free(arr);
}

void test02() {
    //通用指针 void*
    //malloc返回的类型是 void*
    int arr[5] = { 10,20,30,40,50 };
    void* p = arr;
    //int val1 = *p + 100;//报错 通用指针不能解引用，也不能做算术运算
    int* p_int = (int*)p;
    int val2 = (*p_int) + 100;
    printf("val2=%d\n", val2);
}

void test03() {
    void* p = malloc(10 * sizeof(int));
    if (p == NULL) {
        printf("malloc failed.\n");
        return;
    }
    int* p_int = (int*)p;
    for (int i = 0; i < 10; i++) {
        //p[i] = 'a' + i;
        p_int[i] = 'a' + i;
    }
    for (int i = 0; i < 10; i++) {
        //printf("%c----\n", p[i]);
        printf("%c----\n", p_int[i]);
    }
    free(p);
}

void test04() {
    //不能free栈区内存
    //不能重复free
    //只能free指向申请得到的堆区的首字节指针，指针向后移动了再去free会报错
    int arr[10] = { 1,2,3 };
    int* p = arr;
    free(p);
}

void test05() {
    int* p = malloc(24);
    int* old_p = p;
    p++;
    p++;
    //free(p);
    free(old_p);
}


int main(void) {
    //test01();
    //test02();
    //test03();
    //test04();//报错 debug assertion failed 不能free栈区内存
    test05();
    return 0;
}
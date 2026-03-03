#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*

*/

void test1() {
    int num = 10;
    int num2 = 9990;

    int* p1 = &num;//指向num
    printf("%d\n", *p1);

    *p1 = 10086;//改变num的值
    printf("%d\n", *p1);

    p1 = &num2;//改变p1的指向
    printf("%d\n", *p1);

    int** pp1 = &p1;//指向指针的指针
    *pp1 = &num;//同样是改变p1的指向

    printf("%d\n", *p1);
}

void change_int_by_int(int num) {
    num = 10086;
}

void change_int_by_pointer(int* p1) {
    *p1 = 999;
}

int global_num = 666;
void change_pointer_by_pointer(int *p1) {
    p1 = &global_num;
    printf("in change_pointer_by_pointer num=%d\n", *p1);
}

void change_pointer_by_pointerpointer(int **pp) {
    *pp = &global_num;
}

void test2() {
    int num = 10;
    int* p = &num;
    int** pp = &p;
    printf("%d\n", num);

    change_int_by_int(num);
    printf("change_int_by_int %d\n", num);

    change_int_by_pointer(p);
    printf("change_int_by_pointer %d\n", num);

    change_pointer_by_pointer(p);
    printf("after change_pointer_by_pointer %d\n", num);

    change_pointer_by_pointerpointer(pp);
    printf("change_pointer_by_pointerpointer %d\n", num);
}

void test3() {
    //数组指针 指向数组的指针
    int arr[2] = { 1,2 };

    //值相同 但类型不同
    int* p = arr;//数组名退化为指针，指向第一个元素的首地址
    int(* parr)[2]=&arr;//数组指针 相当于&arr 指向整个数组的首地址

    printf("sizeof p = %d\n", sizeof(p));
    printf("sizeof parr = %d\n", sizeof(parr));
    printf("%d\n", p[0]);
    printf("%d\n", parr[0]);//等价于*(parr+0) 打印整个数组名 
    //此时数组名退化为首元素第一个字节的地址 相当于打印一个地址

    printf("%d\n", **parr);
    printf("%d\n", *parr[0]);
    printf("%d\n", parr[0][0]);
}

void test4() {
    //指针数组 装着指针的数组
    int a = 1, b = 2, c = 3;
    int* p[6] = { &a,&b,&c };//先于[]结合，是个数组，数组里装int*
    for (int i = 0; i < 3; i++) {
        printf("%d ", *p[i]);
    }
    printf("\n");
}

void test5() {
    //const的效果
    int num1 = 10;
    int num2 = 20;

    int* const p1 = &num1;//const 和 p 结合
    //p1 = &num2;//报错 指针的指向不可变
    *p1 = 11;//指针指向的元素的值可变

    int const* p2 = &num2;//const 和 *p 结合
    p2 = &num1;//指针的指向可变
    //*p2 = 22;//报错 指针指向的元素的值不可变

    const int * p3 = &num2;//const 和 *p 结合
    p3 = &num1;//指针的指向可变
    //*p3 = 22;//报错 指针指向的元素的值不可变
}


int main(void) {
    //test1();
    //test2();
    //test3();
    test4();
    return 0;
}
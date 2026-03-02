#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*
字符串
*/

void test01() {
    char str1[10] = "hello";
    char str2[5] = { 'h','e','l','l','o' };//没有'\0'不是字符串
    char str3[10]= { 'h', 'e', 'l', 'L', 'o', '\0', 'a', 'a', 'b', '\0' };//字符串存不了'\0'
}

void test02() {
    char ch1 = '0';//字符0 的ASCII码值 48
    char ch2 = 0;//数字0
    char ch3 = '\0';//\0 的ASCII是0值

    char str1[5] = { 'h', 'e', 'l', 'l', '0' };// str1不是字符串。 它只是字符数组。 
    char str2[5] = { 'h', 'e', 'l', 'l', '\0' };// 是字符串
    char str3[5] = { 'h', 'e', 'l', 'l', 0 };//是字符串
    char str4[6] = { 'h', 'e', 'l', 'l' , '0' };//是字符串，部分初始化末尾初始化为0
}

void test03() {
    printf("%s", "hello world");
    printf("%d\n", sizeof("hello"));
    char* p = "hello";
    //*p = 'H';//只读数据段不能修改
    printf("%c", *p++);
    printf("%c", *p++);
    printf("%c", *p++);
}

void test04() {
    char* p1 = "hello";//p1指向只读数据段 不可通过*p修改"hello"
    char* p2 = &"hello";//可以对"hello"取地址，依然不能对"hello"进行修改
    //此时发生隐式类型转换，&"hello"从数组指针转为一个char型指针，值都是首元素的首字节地址
    char c1 = "hello"[4];
    char* p_elem = "hello" + 4;
    char c2 = *("hello" + 4);
    printf("c1=%c\n *p_elem=%c\n c2=%c\n",c1,*p_elem,c2);
}

void test05() {
    char str1[20 + 1];//数组声明，向系统要了21字节，可以直接存储数据
    char* str2=str1;//只是一个指针，需要让其指向某块内存才能开始使用
    str2[0] = 'h';
    str2[1] = 'e';
    str2[2] = 'l';
    str2[3] = 'l';
    str2[4] = '\0';
    while (*str2 != '\0') {
        printf("%c", *str2++);
    }
}

void test06() {
    char str[50] = "agkajgklajglfajg";
    char str2[] = "hello";//大小为6
    char str3[5] = "hello";//大小为5
    char str4[20] = "hello";
}

void test07() {
    char str[] = "jaklgjkg";//语法糖，在栈上，可修改
    char* p = "ajgkljaklgj";//指针指向只读数据段，不可修改
}

void test08() {
    char str[20] = { 0 };
    scanf("%19s", str);//留一个位置给'\0'
}

int main(void) {
    //test03();
    //test04();
    test05();
    return 0;
}
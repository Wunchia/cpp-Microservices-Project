#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

/*

*/

void test01() {
    char str1[50] = { 0 };
    char str2[] = "123456";
    char* ret = strcpy(str1, str2);
    printf("str1=%s\n", str1);
    printf("str2 = % s\n", str2);
    printf("ret=%s\n", ret);//ret返回的是dest
    printf("(ret==str1)=%d\n",(ret==str1));
}

void test02() {
    char* p1 = "123456";
    char* p2 = "123";
    //strcpy(p1, p2);//p1指向只读数据段,所以不能向p1写入
}

//字符串数组
void test03() {
    char week_days[][10] = {"Monday","Tuseday","Wednesday","Thursday","Friday","Saturday","Sunday"};//按最长的字符串对齐 很浪费内存空间
        //4d 6f 6e 64 61 79 00 00  
        //00 00 54 75 73 65 64 61  
        //79 00 00 00 57 65 64 6e  
        //65 73 64 61 79 00 54 68  
        //75 72 73 64 61 79 00 00  
        //46 72 69 64 61 79 00 00  
        //00 00 53 61 74 75 72 64  
        //61 79 00 00 53 75 6e 64  
        //61 79 00 00 00 00
}

int main(void) {
    /*test01();
    test02();*/
    test03();
    return 0;
}
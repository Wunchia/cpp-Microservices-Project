#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*

*/

void test01() {
    char fruits1[][10] = {//二维数组 语法糖 在栈区定义 
        "apple",
        "banana",
        "cherry"
    };

    char* fruits2[] = {//指针数组 每个指针指向数据段的一个字符串
        "apple",
        "banana",
        "cherry"
    };

    char(*p1)[10] = fruits1;//数组指针 指向一个长度为10的字符数组
    printf("%s\n", *p1);//解引用后得到该一维数组的首地址
    printf("%s\n", *(p1 + 1));//+1时 移动十个字节（一个字符数组的长度）

    char** pp2 = fruits2;//二级指针 指向指针的指针
    printf("%s\n", *pp2);//解引用后得到该字符串的首地址
    printf("%s\n", *(pp2 + 1));//+1时 移动一个指针的长度 指向下一个指针
}

int main(void) {

    test01();

    return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
在main函数当中，先写出下列代码，用两种不同的方式来定义实现字符串数组：
// char类型二维数组实现字符串数组
char fruits1[][10] = {
"apple",
"banana",
"cherry"
};
// char*指针数组实现字符串数组
char *fruits2[] = {
"apple",
"banana",
"cherry"
};
请完成以下编程或者回答相应的问题。

题目一：
请分别遍历 fruits1 和 fruits2这两个字符串数组，输出每个字符串的内容及其长度。

题目二：
请分别将两个字符串数组中的第一个字符串，修改成"orange"。
首先你需要回答：基于"="运算符直接赋值修改，能不能完成这样的操作？如果不能为什么？
提示：通过一定的手段，两个都可以完成修改。参考代码仅提供一种实现方式，若你能够实现，亦可采用自己的实现。

题目三：
请分别将两个字符串数组中的第二个字符串"banana"中的第一个字符'b'，修改成'B'。
首先你需要回答：基于"="运算符直接赋值修改，能不能完成这样的操作？如果不能为什么？
提示：通过一定的手段，两个都可以完成修改。参考代码仅提供一种实现方式，若你能够实现，亦可采用自己的实现。

题目四：
请自行定义初始化一个字符串数组fruits3，使得这个字符串数组既可以通过"="直接修改整个字符串的内容，也可以利用"="修改某个字符串的某个字符。
提示：实现方式不唯一，参考代码仅提供一种实现参考。
*/


int main(void) {
    char fruits01[][10] = { "apple","banana","cherry" };
    char* fruits02[] = { "apple","banana","cherry" };

    //Q1
    char(* p1)[10] = fruits01;
    for (int i = 0; i < 3; i++) {
        printf("%s len = %d\n", *p1,strlen(*p1));
        p1++;
    }
    
    for (int i = 0; i < 3; i++) {
        printf("%s len = %d\n", fruits02[i],strlen(fruits02[i]));
    }
    printf("============\n");

    //Q2
    //fruits01是一个定义在栈区的二维字符数组，fruits01本身是一个数组名（const pointer）不能改变其指向,修改其内容需要使用strcpy
    //fruits02是一个指针数组，其中每一个指针（pointer_to_const）都指向只读数据段，指向的内容不可修改，但可以修改其指向
    
    strcpy(fruits01[0], "orange");
    p1 = fruits01;
    for (int i = 0; i < 3; i++) {
        printf("%s len = %d\n", *p1, strlen(*p1));
        p1++;
    }
    fruits02[0] = "orange";
    for (int i = 0; i < 3; i++) {
        printf("%s len = %d\n", fruits02[i], strlen(fruits02[i]));
    }

    printf("============\n");

    //Q3
    //fruits01可以，其定义在栈区，数组内容可以直接修改
    //fruits02不可以，其指向只读数据段，内容不可修改
    fruits01[1][0]='B';
    p1 = fruits01;
    for (int i = 0; i < 3; i++) {
        printf("%s len = %d\n", *p1, strlen(*p1));
        p1++;
    }
    fruits02[1] = "Banana";
    for (int i = 0; i < 3; i++) {
        printf("%s len = %d\n", fruits02[i], strlen(fruits02[i]));
    }
    printf("=============\n");
    //Q4
    char* fruits03[3];
    fruits03[0] = (char*)malloc(sizeof(char) * 10);
    fruits03[1] = (char*)malloc(sizeof(char) * 10);
    fruits03[2] = (char*)malloc(sizeof(char) * 10);
    strcpy(fruits03[0], "apple");
    strcpy(fruits03[1], "banana");
    strcpy(fruits03[2], "cherry");
    for (int i = 0; i < 3; i++) {
        printf("%s \n", fruits03[i]);
    }
    //fruits03[0] = "orange";//这样写会丢失之前申请的堆空间导致内存泄露，并且让fruits03[0]指向只读数据段
    strcpy(fruits03[0],"orange");
    for (int i = 0; i < 3; i++) {
        printf("%s \n", fruits03[i]);
    }
    fruits03[1][0] = 'B';
    for (int i = 0; i < 3; i++) {
        printf("%s \n", fruits03[i]);
    }
    for (int i = 0; i < 3; i++) {
        free(fruits03[i]);
    }
    return 0;
}
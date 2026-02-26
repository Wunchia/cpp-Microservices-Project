#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*
随机数
*/

void test01() {
    //固定随机种子，生成的是伪随机数
    srand(3);
    for (int i = 0; i < 10; i++) {
        printf("%d\n", rand());
    }
}
void test02() {
    //时间是不会重复的，用时间作随机种子
    printf("%d \n", time(NULL));
    srand(time(NULL));
    for (int i = 0; i < 10; i++) {
        printf("%d\n", rand());
    }
}

void test03() {
    //理解time()函数
    time_t current_time=0;  // 定义变量，此时内容不确定
    printf("调用前 current_time 的值：%ld\n", current_time);  // 垃圾值

    time_t return_value = time(&current_time);  // 调用 time() 函数

    printf("调用后 current_time 的值：%ld\n", current_time);  // 当前时间戳
    printf("返回值 return_value 的值：%ld\n", return_value);  // 同样的当前时间戳

    // 验证两者相等
    printf("两者 %s\n", (current_time == return_value) ? "相等" : "不相等");
}

void test04() {
    //不断重置种子值反而不随机
    for (int i = 0; i < 10; i++) {
        srand(time(NULL));
        printf("%d\n", rand());
    }
}

void test05(int min,int max) {
    printf("%d\n", RAND_MAX);
    srand(time(NULL));
    for (int i = 0; i < 10; i++) {
        printf("%d\n", min + (rand() / (RAND_MAX / (max - min + 1) + 1)));
    }
}

void test06() {
    srand(time(NULL));
    for (int i = 0; i < 10; i++) {
        printf("%d\n", rand() % 10);
    }
}

int main(void) {
    test01();
    test02();
    test03();
    test04();
    test05(10,20);
    test06();
    return 0;
}
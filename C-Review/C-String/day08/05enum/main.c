#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*

*/

enum vip_status {
    SVIP_0 = 1000,
    SVIP_1,
    SVIP_2
};

typedef enum {
    RED,
    BLUE,
    YELLOW
}Colors;

typedef enum {
    TEST1,
    TEST2,
    TEST3
}Tests;

int speed(enum vip_status status) {
    if (status == SVIP_0) {
        return 10;
    }
    else if (status == SVIP_1) {
        return 100;
    }
    else if (status == SVIP_2) {
        return 1000;
    }
}

void test01() {
    printf("%d\n", SVIP_0);
    printf("%d\n", SVIP_1);
    printf("%d\n", SVIP_2);
    printf("%d\n", RED);
    printf("%d\n", BLUE);
}

void test02() {
    Colors c = RED;
    c = TEST1;
    if (c == RED) {
        printf("enum ������\n");
    }
}

int main(void) {
    test01();
    test02();
    return 0;
}
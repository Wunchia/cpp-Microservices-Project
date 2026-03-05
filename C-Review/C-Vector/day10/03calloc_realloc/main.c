#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
/*

*/

void test01() {
    int* p = calloc(9, sizeof(int));
    if (p == NULL) {
        printf("calloc failed in test01\n");
        return;
    }
    for (int i = 0; i < 9; i++) {
        printf("======%d\n", p[i]);
    }
    free(p);
}

void test02() {
    char* p = malloc(40);
    
    //p = realloc(p, 60);//错误写法 realloc失败的时候不会直接free掉空间 会返回NULL
    //这样写会导致p原本指向的空间没有free掉的时候就被重新指向NULL 内存泄露 数据丢失

    char* new_p = realloc(p, 60);

    if (new_p == NULL) {
        printf("realloc failed\n");
        free(p);
        return;
    }
    p = new_p;

}

int main(void) {
    test01();
    return 0;
}
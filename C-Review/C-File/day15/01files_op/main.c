#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*

*/

void test1() {
    FILE* fp = fopen("1.txt", "r");
    if (fp == NULL) {
        printf("fopen failed.\n");
        return;
    }
    printf("fopen success.\n");
    int ch1 = fgetc(fp);
    printf("ch=%c\n", ch1);
    int ch2 = fgetc(fp);
    printf("ch2 = %c\n", ch2);
    printf("ch3 = %c\n", fgetc(fp));
    printf("ch4 = %c\n", fgetc(fp));
    printf("ch5 = %c\n", fgetc(fp));
    printf("ch6 = %c\n", fgetc(fp));
    printf("ch7 = %c\n", fgetc(fp));
    printf("ch8 = %d\n", fgetc(fp));
    printf("ch9 = %c\n", fgetc(fp));
    printf("ch10 = %d\n", fgetc(fp));
    printf("ch11 = %d\n", fgetc(fp));
    printf("ch12 = %d\n", fgetc(fp));
    fclose(fp);
}

void test2() {
    FILE* fp = fopen("1.txt", "r");
    if (fp == NULL) {
        printf("fopen failed.\n");
        return;
    }
    int ch;
    while ((ch = fgetc(fp)) != -1) {
        printf("-----%c\n", ch);
    }
    fclose(fp);
}

void test3() {
    FILE* fp = fopen("1.txt", "w");
    if (fp == NULL) {
        printf("fopen failed.\n");
        return;
    }
    fputc('a', fp);
    fputc('b', fp);
    fputc('c', fp);
    fputc('d', fp);
    fputc('\n', fp);
    fputc('e', fp);
    fputc('f', fp);
    fputc('g', fp);
    fclose(fp);
}

void test4() {
    FILE* src_fp = fopen("1.txt", "r");
    if (src_fp == NULL) {
        printf("fopen src failed.\n");
        return;
    }
    FILE* dest_fp = fopen("1_copey.txt", "w");
    if (dest_fp == NULL) {
        printf("fopen dest failed.\n");
        fclose(src_fp);
        return;
    }

    int ch;
    while ((ch = fgetc(src_fp)) != -1) {
        fputc(ch, dest_fp);
    }
    fclose(src_fp);
    fclose(dest_fp);
}

void test5() {
    FILE* dest_fp = fopen("1_copey.txt", "w");
    if (dest_fp == NULL) {
        printf("fopen dest failed.\n");
        return;
    }
    fclose(dest_fp);
}

int main(void) {
    test5();
    return 0;
}
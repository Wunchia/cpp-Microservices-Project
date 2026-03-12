#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
/*

*/

void test1() {
    FILE* fp = fopen("1.txt", "r");

    if (fp == NULL) {
        printf("fopen failed.\n");
        return;
    }

    char buf[50] = { 0 };
    char* ret = fgets(buf, 50, fp);
    printf("%s", buf);
    ret = fgets(buf, 50, fp);
    printf("%s\n", buf);
}

void test2() {
    FILE* fp = fopen("1.txt", "r");
    if (fp == NULL) {
        printf("fopen failed.\n");
        return;
    }
    char buf[5] = { 0 };
    char* ret1 = fgets(buf, 5, fp);
    printf("%s\n", ret1);
    char* ret2 = fgets(buf, 5, fp);
    printf("%s\n", ret2);
}

void test3() {
    FILE* fp = fopen("1.txt", "r");
    if (fp == NULL) {
        printf("fopen failed.\n");
        return;
    }
    char buf[5] = { 0 };
    char* ret = NULL;
    while ((ret = fgets(buf, sizeof(buf), fp)) != NULL) {
        printf("---%s---\n", buf);
    }
    fclose(fp);
}

void test4() {
    FILE* fp = fopen("1.txt", "w");
    if (fp == NULL) {
        printf("fopen failed.\n");
        return;
    }
    fprintf(fp, "%d %d-----%lf\n", 10, 111, 3.66);
    fclose(fp);
}

void test5() {
    FILE* fp = fopen("1.txt", "r");
    if (fp == NULL) {
        printf("fopen failed.\n");
        return;
    }
    int num = 0;
    double d1 = 0.0;
    fscanf(fp, "%d %lf", &num, &d1);
    printf("%d---%lf\n", num, d1);
}

void test6() {
    int arr[] = { 10,11,12,13,14,15 };
    FILE* fp = fopen("1.dat", "wb");
    if (fp == NULL) {
        printf("fopen failed.\n");
        return;
    }
    size_t ret = fwrite(arr, sizeof(int), 6, fp);

    printf("ret=%d\n", ret);
    fclose(fp);
}

void test7() {
    FILE* fp = fopen("1.dat", "rb");
    if (fp == NULL) {
        printf("fopen failed.\n");
        return;
    }
    int arr[] = { 0,0,0,0,0,0,0,0,0,0,0,0,0 };
    size_t ret = fread(arr, sizeof(int), 13, fp);
    printf("ret=%d\n", ret);
    for (int i = 0; i < 13; i++) {
        printf("--%d\n", arr[i]);
    }
    fclose(fp);
}

typedef struct student {
    int id;
    char name[25];
    int chinese;
    int math;
} Student;

void test8() {
    Student s1 = { 1001, "张三", 95, 88 };
    FILE* fp = fopen("student.dat", "wb"); // wb 表示以二进制写模式打开

    if (fp == NULL) return;

    // --- 序列化：将结构体直接写入文件 ---
    // 参数含义：数据地址, 每个元素大小, 写入几个元素, 文件指针
    size_t count = fwrite(&s1, sizeof(Student), 1, fp);

    if (count > 0) {
        printf("序列化成功，数据已存入 student.dat\n");
    }

    fclose(fp);

    // --- 反序列化：从文件读回结构体 ---
    Student s2;
    fp = fopen("student.dat", "rb"); // rb 表示以二进制读模式打开
    if (fp) {
        fread(&s2, sizeof(Student), 1, fp);
        printf("反序列化结果：ID=%d, 姓名=%s, 语文=%d\n", s2.id, s2.name, s2.chinese);
        fclose(fp);
    }
}

void test9() {
    FILE* fp = fopen("2.txt", "r");

    printf("errno2 = %d\n", errno);
    printf("--------%s\n", strerror(errno));
    printf("--------%s\n", strerror(1));
    printf("--------%s\n", strerror(2));
    printf("--------%s\n", strerror(3));
    printf("--------%s\n", strerror(4));
    printf("====================\n");
    perror("1111");
    fp = fopen("2.txt", "r");
    perror("2.txt");
}

int main(void) {
    test9();
    return 0;
}
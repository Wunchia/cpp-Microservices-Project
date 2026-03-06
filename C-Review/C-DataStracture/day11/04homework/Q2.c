#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
你的任务是使用qsort函数对这个结构体数组进行排序：
规则1：将全体结构体对象，按照学生成绩从高到低进行排序。
规则2：先将全体结构体对象，按照学生成绩从低到高进行排序，如果成绩一致，则那么按照名字的字典顺序进行排序。
最后，你还需要实现一个函数用于打印整个学生数组：
 void print_students(Student stus[], int size);
*/

typedef struct {
    char name[25];
    int score;
} Student;

void print_student(Student stus[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%s -- %d\n ",stus[i].name, stus[i].score);
    }
    printf("\n");
}

int compare_students_by_score(const void* a, const void* b) {
    Student* pa = a;
    Student* pb = b;
    return pb->score - pa->score;
}

int compare_students_by_score_and_name(const void* a, const void* b) {
    Student* pa = a;
    Student* pb = b;
    if (pa->score != pb->score) {
        return pa->score - pb->score;
    }
    else {
        return strcmp(pa->name, pb->name);
    }
}

int main(void) {
    Student stus[] = {
        {"Alice", 85},
        {"Bob", 92},
        {"Charlie", 85},
        {"David", 85},
        {"Eve", 92},
        {"Frank", 75},
        {"Grace", 85},
        {"Hannah", 95},
        {"Ivy", 78},
        {"Jack", 85}
    };

    print_student(stus, 10);
    qsort(stus, 10, sizeof(Student), compare_students_by_score);
    print_student(stus, 10);
    qsort(stus, 10, sizeof(Student), compare_students_by_score_and_name);
    print_student(stus, 10);

    return 0;
}
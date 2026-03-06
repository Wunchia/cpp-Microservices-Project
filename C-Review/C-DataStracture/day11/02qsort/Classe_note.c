#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define ARR_LEM(arr)(sizeof(arr)/sizeof(arr[0]))

void print_arr(int* arr, int len) {
	for (int i = 0; i < len; i++) {
		printf("%d  ", arr[i]);
	}
	printf("\n");
}

int compare_int(const void* a, const void* b) {
	int* pa = a;
	int* pb = b;
	return *pa - *pb;
}

void test01() {
	printf("==== in test01 ====\n");
	int arr[13] = { 10,30,1,5,98,8,7,65,35,15,1256,56,4 };
	print_arr(arr,13);
	qsort(arr, 13, sizeof(int), compare_int);
	print_arr(arr, 13);
	printf("==== test01 end ====\n");
}

typedef struct student {
	int id;
	char name[10];
	double Chinese_score;
	double Math_score;
	double English_score;
}Student;

typedef enum sort_by {
	id,
	score
}Sort_by;

int compare_student_by_id(const void* a, const void* b) {
	Student* s1 = a;
	Student* s2 = b;
	return s1->id - s2->id;
}

int compare_student_by_Score(const void* a, const void* b) {
	Student* s1 = a;
	Student* s2 = b;
	if (s1->Chinese_score != s2->Chinese_score) {
		return s2->Chinese_score - s1->Chinese_score;
	}
	else if (s1->Math_score != s2->Math_score) {
		return s2->Math_score - s1->Math_score;
	}
	else {
		return s2->English_score - s1->English_score;
	}
}

void print_student(Student *arr, int len, Sort_by flag) {
	for (int i = 0; i < len; i++) {
		if (flag == id) {
			printf("%s 的id是 %d \n", arr[i].name, arr[i].id);
		}
		else if (flag == score) {
			printf("\n%s 的成绩为\n语文:%.2lf 数学:%.2lf 英语:%.2lf \n", 
				arr[i].name, arr[i].Chinese_score, arr[i].Math_score, arr[i].English_score);
		}
	}
}

void test02() {
	printf("==== In test02 ====\n");
	Student s1 = { 1, "zhangsan1", 90, 70, 70 };
	Student s2 = { 9, "zhangsan9", 90, 80, 75 };
	Student s3 = { 3, "zhangsan3", 80, 60, 80 };
	Student s4 = { 4, "zhangsan4", 70, 80, 69 };
	Student s5 = { 2, "zhangsan2", 100, 40, 80 };
	Student s6 = { 7, "zhangsan7", 95, 90, 81 };
	Student s7 = { 6, "zhangsan6", 80, 100, 80 };
	Student student_arr[7] = { s1,s2,s3,s4,s5,s6,s7 };
	print_student(student_arr, 7, id);
	qsort(student_arr, 7, sizeof(Student), compare_student_by_id);
	printf("---排序后---\n");
	print_student(student_arr, 7, id);
	printf("======\n");
	print_student(student_arr, 7, score);
	qsort(student_arr, 7, sizeof(Student), compare_student_by_Score);
	printf("---排序后---\n");
	print_student(student_arr, 7,score);
	printf("==== End test02 ====\n");
}

int compare_string(const void** a, const void** b) {
	char* str1 = *(const char**)a;
	char* str2 = *(const char**)b;
	return strcmp(str1, str2);
}

void print_str(char *str[],int len) {
	for (int i = 0; i < len; i++) {
		printf("%s ", str[i]);
	}
	printf("\n");
}

void test03() {
	printf("==== In test03 ====\n");
	char* a[] = { "yoka","abc","kevin","def","steven","cuki" };
	print_str(a,6);
	qsort(a, 6, sizeof(char*), compare_string);
	print_str(a, 6);
	printf("==== End test03 ====\n");
}


int main(void){
	test01();
	test02();
	test03();

	return 0;
}
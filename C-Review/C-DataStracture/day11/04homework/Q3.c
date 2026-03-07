//编写一个C语言程序，完成以下任务：
//首先，从键盘录入一个整数，表示接下来要录入的字符串的数量。
//紧接着根据这个数量，从键盘连续录入字符串，每次都会将一整行键盘录入成一个字符串
//这些被录入的字符串需要存入一个字符串数组，然后将该字符串数组按照以下两种规则排序遍历打印：
//1.按照字符串的长度，从长到短排序
//2.先按照字符串的长度从短到长排序，长度一致的字符串按照字典顺序排序。

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int compare_01(const void*a,const void*b) {
	const char* pa = *(const char**)a;
	const char* pb = *(const char**)b;
	return strlen(pb) - strlen(pa);
}

int compare_02(const void* a, const void* b) {
	const char* pa = *(const char**)a;
	const char* pb = *(const char**)b;
	if (strlen(pa) != strlen(pb)) {
		return strlen(pa) - strlen(pb);
	}
	return strcmp(pa, pb);
}

void print_str(char** str, int len) {
	for (int i = 0; i < len; i++) {
		printf(" %s ", str[i]);
	}
	printf("\n");
}

int main(void) {
	int n = 0;
	printf("请输入一个整数\n");
	scanf("%d", &n);
	while (getchar() != '\n');
	char** str = (char**)malloc(sizeof(char*)* n);
	if (str == NULL) {
		printf("malloc of str failed\n");
		return -1;
	}
	char buffer[1024];
	for (int i = 0; i < n; i++) {
		printf("请输入第%d行字符串：\n", i+1);
		fgets(buffer, 1024, stdin);
		buffer[strcspn(buffer,"\n")] = '\0';
		str[i] = (char*)malloc(strlen(buffer) + 1);
		if (str[i] == NULL) {
			printf("malloc of str[%d] failed\n", i);
			return -1;
		}
		strcpy(str[i],buffer);
	}
	print_str(str, n);
	printf("====第一次排序====\n");
	qsort(str, n, sizeof(char*), compare_01);
	print_str(str, n);
	printf("====第二次排序====\n");
	qsort(str, n, sizeof(char*), compare_02);
	print_str(str, n);
	for (int i = 0; i < n; i++) {
		free(str[i]);
	}
	free(str);
	return 0;
}
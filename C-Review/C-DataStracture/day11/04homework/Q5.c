//首先给定以下字符数组：

//请你先利用qsort函数将此字符串数组，按照逆字典顺序排序。然后将这个字符串数组中的每一个字符串，按照从前到后的顺序，拼接组装成一个新字符串，并且在拼接时删除每个子字符串的第一个字符。
//这样你将得到Linux之父Linus Torvalds的名言：“Talk is cheap, show me the code.”
//要求使用动态分配内存来存储结果字符串，函数声明如下：
//char* concat_strs(char* strings[], int count);

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_str(const void* a, const void* b) {//a,b是"Talk","is"这样的字符串，是指针数组（指向指针的指针）
	char* pa = *(const char**)a;//强转为二级指针，再解引用
	char* pb = *(const char**)b;
	return strcmp(pb, pa);
}

char* concat_strs(char* strings[], int count) {
	char* quota = (char*)malloc(sizeof(char) * 33);
	if (quota == NULL) {
		printf("malloc failed in concat_strs\n");
		return NULL;
	}
	char* j = NULL;
	int k = 0;
	for (int i = 0; i < count; i++) {
		j = strings[i];
		j++;
		while (*j != '\0') {
			quota[k++] = *j;
			j++;
		}
	}
	quota[k] = '\0';
	return quota;
}

int main(void) {
	char* strings[] = {
		"4show ",
		"1code.",
		"5cheap, ",
		"6is ",
		"7Talk ",
		"2the ",
		"3me "
	};
	
	qsort(strings, 7, sizeof(char*), compare_str);
	char*quota=concat_strs(strings, 7);
	if (quota == NULL) {
		printf("concat_strs failed to malloc and return\n");
	}
	printf("%s\n", quota);
	free(quota);
	quota = NULL;
	return 0;
}
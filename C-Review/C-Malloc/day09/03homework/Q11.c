//编写程序，从键盘输入输入中读取一个整数n，动态分配一个长度为n的整型数组。
//将数组元素初始化为1, 2, 3, ..., n，并输出打印数组内容，最后释放内存。

//注意 :
//初始化内存块时可以直接使用下标来操作内存块。
//遍历打印数组元素取值时，请使用指针来实现操作。

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int len = 0;
	scanf("%d", &len);
	int* p = (int*)malloc(len * sizeof(int));

	if (p == NULL) {
		printf("malloc failed\n");
		return -1;
	}

	for (int i = 0; i < len; i++) {
		p[i] = i+1;
	}
	int* old_p = p;
	for (int i = 0; i < len; i++) {
		printf("%d ", * p++);
	}
	printf("\n");
	free(old_p);
	old_p = NULL;
	p = NULL;
	return 0;
}
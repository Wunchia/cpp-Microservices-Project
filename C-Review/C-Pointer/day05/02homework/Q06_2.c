#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
//给定任意一个非负十进制整数，请利用递归的方式，求解它的二进制表示方式
//基本的思路是：把该整数除以2得到余数，然后倒着输出余数。

void dtob(int d,int b[],int *p) {
	if (d == 1 || d == 0) {
		b[(*p)++] = d % 2;
		return;
	}
	b[(*p)++] = d % 2;	
	dtob(d / 2,b,p);
}

int main(void) {
	int binary[32] = { 0 };
	int top = 0;
	printf("请输入一个非负十进制整数：\n");
	int d = 0;
	scanf("%d", &d);
	printf("其转为二进制为：\n");
	dtob(d, binary, &top);
	while (top > 0) {
		printf("%d", binary[--top]);
	}
	printf("\n");

	return 0;
}
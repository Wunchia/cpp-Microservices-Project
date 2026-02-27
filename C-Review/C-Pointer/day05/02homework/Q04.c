//编写函数实现以下功能：
//键盘录入一个正整数，请判断它是否是一个素数，然后控制台输出对应的结果。要对键盘录入的数据做参数校验，素数是一个大于1的自然数，它仅能被1和自身整除。
//键盘录入两个整数：底(base)和幂指数(exponent)，计算base的exponent次幂，并打印输出对应的结果。（注意底和幂指数都可能是负数）
//提示：求幂运算时，基础的思路就是先无脑把指数转换成正数，然后累乘，最后再根据指数是否是负数决定是否取倒数。

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
bool is_prime(int a) {
	int n = sqrt(a);
	for (int i = 2; i <= n; i++) {
		if (a % i == 0) {
			return false;
		}
	}
	return true;
}

double exp(int base, int exponent) {
	bool reciprocal=false;
	if (exponent > 0) {
		reciprocal = false;
	}
	else if (exponent < 0) {
		reciprocal = true;
	}
	else {
		return 1;
	}
	int temp = base;
	for (int i = 1; i < exponent; i++) {
		base *= temp;
	}
	if (reciprocal == true) {
		return 1.0 / base;
	}
	else {
		return base;
	}
}

int main(void) {
	printf("请输入一个正整数：\n");
	int a = 0;
	scanf("%d", &a);
	while (getchar() != '\n');
	if (is_prime(a)) {
		printf("%d是素数\n", a);
	}
	else {
		printf("%d不是素数\n", a);
	}

	printf("请输入两个正整数分别作为底数和幂指数：\n");
	int b = 0, e = 0;
	scanf("%d %d", &b, &e);
	while (getchar() != '\n');
	printf("%d的%d次幂等于%.2lf\n", b, e, exp(b, e));
	return 0;
}
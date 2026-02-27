//要求至少提供四种运算加减乘除，如下：
//
//int add(int a, int b);
//int subtract(int a, int b);
//int multiply(int a, int b);
//float divide(int a, int b);
//并且在结束进程时，打印总共执行操作的次数。（也就是这些函数调用的次数）
//
//注意：除法的实现，要求判断除数不为0，并且在除数为0时使用exit表示异常退出进程。

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static int add_count = 0;
static int sub_count = 0;
static int mul_count = 0;
static int div_count = 0;

double add(double a, double b) {
	add_count++;
	return a + b;
}

double subtract(double a, double b) {	
	sub_count++;
	return a - b;
}

double multiply(double a, double b) {
	mul_count++;
	return a * b;
}

double divide(double a, double b) {
	if (b == 0) {
		printf("错误，除数不能为0\n");
		exit(EXIT_FAILURE);
	}
	div_count++;
	return a / b;
}

void print_count(int flag) {
	if (flag == 1) {
		printf("执行加法操作%d次\n", add_count);
		printf("执行减法操作%d次\n", sub_count);
		printf("执行乘法操作%d次\n", mul_count);
		printf("执行除法操作%d次\n", div_count);
	}
	int sum = add_count + sub_count + mul_count + div_count;
	printf("共计执行运算%d次\n", sum);
}

int main(void) {
	while (true) {
		printf("请输入需计算的表达式：\n");
		double a = 0, b = 0;
		char op = 0;
		scanf("%lf %c %lf", &a, &op, &b);
		while (getchar() != '\n');
		switch (op) {
		case '+':
			printf("%.2lf + %.2lf = %.2lf\n", a, b, add(a, b));
			break;
		case '-':
			printf("%.2lf - %.2lf = %.2lf\n", a, b, subtract(a, b));
			break;
		case '*':
			printf("%.2lf * %.2lf = %.2lf\n", a, b, multiply(a, b));
			break;
		case '/':
			printf("%.2lf / %.2lf = %.2lf\n", a, b, divide(a, b));
			break;
		default:
			printf("输入错误\n");
		}
		printf("是否继续？(y/n)");
		char ch = 0;
		scanf(" %c", &ch);
		while (getchar() != '\n');
		if (ch != 'y') {
			break;
		}
		/*else {
			print_count(1);
		}*/
	}
	print_count(0);
	return 0;
}
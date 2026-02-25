#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int main(void) {
	double a = 0;
	double b = 0;
	char c = 0;
	char ch = 0;
	do {
		printf("请输入需要计算的表达式（例如：12.7+3.5）:\n");
		scanf("%lf%c%lf", &a, &c, &b);
		switch (c) {
		case '+':
			printf("计算的结果是：%.2lf + %.2lf = %.2lf\n", a, b, a + b);
			break;
		case '-':
			printf("计算的结果是：%.2lf - %.2lf = %.2lf\n", a, b, a - b);
			break;
		case '*':
			printf("计算的结果是：%.2lf * %.2lf = %.2lf\n", a, b, a * b);
			break;
		case '/':
			if (b == 0) {
				printf("Error：除数为0！\n");
				ch = 'y';
				continue;
			}
			else {
				printf("计算的结果是：%.2lf / %.2lf = %.2lf\n", a, b, a / b);
			}
			break;
		default:
			printf("输入错误！请重新输入\n");
			ch = 'y';
			continue;
		}
		ch = 0;
		printf("是否继续计算？（输入'y/Y'继续，其他任意键结束）\n");
		scanf(" %c", &ch);
	} while (ch == 'y' || ch == 'Y');
	return 0;
}
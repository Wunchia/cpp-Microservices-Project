#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*

*/
int main(void) {
    double num1 = 0;
    double num2 = 0;
    char operator=0;
    double result = 0;
    char buffer[100];
    while (1) {
        printf("请输入需要计算的表达式（例如：12.7+3.5）:\n");
        int ret=scanf("%lf %c%lf", &num1, &operator,&num2);
        while (getchar() != '\n');
        if (ret != 3) {
			printf("输入格式错误，请重新输入！\n");
            continue;
        }
        switch (operator) {
            case '+':
                result = num1 + num2;
				break;
            case '-':
                result = num1 - num2;
                break;
            case '*':
                result = num1 * num2;
                break;
            case '/':
                if (num2 == 0) {
					printf("除数不能为零，请重新输入！\n");
                    continue;
                }
                else {
                    result = num1 / num2;
                    break;

                }
            default:
				printf("不支持的运算符，请重新输入！\n");
                continue;
        }
        printf("计算的结果是：%.2lf %c %.2lf = %.2lf\n", num1, operator,num2, result);
        printf("是否继续计算？（输入'y/Y'继续，其他任意键结束)\n");
        char ch = 0;
        scanf(" %c", &ch);
        while (getchar() != '\n');
        if (ch != 'y' && ch != 'Y') {
            break;
        }
    }
    return 0;
}
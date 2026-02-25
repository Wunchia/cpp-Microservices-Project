#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int main(void) {
	int input = -1;
	int res = 0;

	do {
		printf("=======记账程序菜单=======\n");
		printf("0.清空账户余额\n");
		printf("1.往账户上存钱\n");
		printf("2.从账户上取钱\n");
		printf("3.显示当前余额\n");
		printf("4.推出程序\n");
		printf("请选择操作（0-4）：\n");
		scanf("%d", &input);
		switch (input) {
		case 0:
			res = 0;
			printf("余额已清空。\n");
			break;
		case 1:
			printf("请输入存款金额：\n");
			int in=0;
			scanf("%d", &in);
			res += in;
			printf("成功存款%d元\n", in);
			break;
		case 2:
			printf("请输入取款金额：\n");
			int out=0;
			scanf("%d", &out);
			if (out > res) {
				printf("取款失败，余额不足\n");
			}
			else {
				res -= out;
				printf("成功取款%d元\n", out);
			}
			break;
		case 3:
			printf("当前账户余额为%d元\n", res);
			break;
		case 4:
			printf("即将退出程序\n");
			break;
		default:
			printf("输入错误，请重新输入！\n");
		}
	} while (input!=4);

	return 0;
}
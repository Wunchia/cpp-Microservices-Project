#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

//编写一个C程序，实现一个简单的猜数字游戏。程序随机生成一个1 - 100之间的数字，用户有5次机会猜这个数字。
//
//要求：
//1. 使用rand()函数生成1 - 100之间的随机数
//2. 使用while循环控制最多猜5次
//3. 每次猜完后给出提示（猜大了、猜小了）
//4. 如果猜对了，使用break语句跳出循环并输出恭喜信息
//5. 如果5次都没猜对，输出正确答案

int main(void) {
	srand(time(NULL));
	int random = rand() % 100 + 1;
	int trys = 5;
	while (trys>0) {
		int guess = 0;
		printf("请输入你猜的数字（1-100）：\n");
		scanf("%d", &guess);
		if (guess == random) {
			printf("猜对了！\n");
			break;
		}
		else if (guess > random) {
			printf("猜大了\n");
		}
		else if (guess < random) {
			printf("猜小了\n");
		}
		trys--;
	}
	printf("机会用尽，答案为：%d\n", random);
	return 0;
}
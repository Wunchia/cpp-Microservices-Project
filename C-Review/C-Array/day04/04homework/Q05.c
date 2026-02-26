//编写程序模拟掷骰子的游戏（每一次投掷，都投掷两个骰子）。每局游戏的规则如下：
//第一次掷的时候：
//如果点数之和为 7 或 11 则获胜；
//如果点数之和为2、3或12则落败；
//其他情况下的点数之和称为“目标”，继续投掷两个骰子。
//在后续的投掷中：
//如果玩家再次掷出“目标”点数则获胜；
//如果掷出7则落败；
//其他情况都忽略，继续投掷两个骰子。
//在每一局游戏结束时，程序都要询问用户是否再玩一次，如果用户输入的回答不是 y 或 Y ，那么就结束游戏，程序此时要打印显示胜败的次数。
//玩家游玩过程程序的输出，大体如下所示：

//提示（请思考三个问题）：
//1.肯定需要使用随机数，那么srand设置种子值，这个函数调用应该放在哪里呢？
//2.在键盘录入是否继续游玩时，如果键盘输入的是"(空格)y"，会发生什么事情？怎么解决？
//3.在键盘录入是否继续游玩时，如果键盘输入的是"yyy"，会发生什么事情？怎么解决？
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int main(void) {
	int dice[6] = { 1,2,3,4,5,6 };
	while (true) {
		srand(time(NULL));
		int point1 = 0;
		int point2 = 0;
		bool target[13] = { false };
		int flag = 1;
		while (true) {
			printf("roll the dice?(press any key to continue)\n");
			char c = 0;
			scanf("%c", &c);
			while (getchar() != '\n');
			point1 = dice[rand() % 6];
			point2 = dice[rand() % 6];
			int sum = point1 + point2;
			printf("You rolled: %d %d,sum_point=%d\n", point1, point2, sum);
			if (flag == 1 && (sum == 7 || sum == 11)) {
				printf("Win!\n");
				break;
			}
			else if (flag == 1 && (sum == 2 || sum == 3 || sum == 12)) {
				printf("Lose!\n");
				break;
			}
			if (flag == 0 && sum == 7) {
				printf("Lose!\n");
				break;
			}
			flag = 0;
			if (target[sum] == true) {
				printf("Win!\n");
				break;
			}
			target[sum] = true;
		}
		char ch = 0;
		printf("Play again?(y/Y means continue)\n");
		scanf(" %c", &ch);
		while (getchar() != '\n');
		if (ch != 'y' && ch != 'Y') {
			break;
		}
	}
	return 0;
}
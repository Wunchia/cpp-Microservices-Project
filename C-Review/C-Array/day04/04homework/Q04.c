#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
//现在有一副扑克牌，去掉大小王。请你写一个随机发牌程序，由用户指定发几张票，然后打印用户得到的手牌。
//
//注：
//
//扑克牌的花色（suit）有四种：梅花（Club）、方块（Diamond）、红心（Heart）、黑桃（Spade）
//
//扑克牌的点数（point）有13种，2~10，J，Q，K，A
int main(void) {
	char suits[4] = { 'C','D','H','S'};
	char points[13] = { '2','3','4','5','6','7','8','9','T','J','Q','K','A' };
	srand(time(NULL));
	char suit, point;
	int suit_index = -1;
	int	point_index = -1;
	int n=0;
	int already_get = 0;
	printf("请输入您需要的手牌数量：\n");
	scanf("%d", &n);
	bool getted[4][13] = { {false} };//避免重复发牌，记录已经发过的牌
	while (already_get < n) {
		suit_index = rand() % 4;
		point_index = rand() % 13;
		suit = suits[suit_index];
		point = points[point_index];
		if (getted[suit][point] == true) {
			printf("重复，重新发牌");
			continue;
		}
		getted[suit][point] = true;
		printf(" %c%c ", suit, point);
		already_get++;
	}
	printf("\n");
	return 0;
}; 
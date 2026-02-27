#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

static int num = 0;
void hanoi(int n, char from, char aux, char to,int need) {
	static int step = 0;
	if (n == 1) {
		step++;
		if (need == step) {
			printf("%d个盘子的汉诺塔问题，第%d步的移动轨迹是：%c--->%c\n",num, need,from, to);
		}
		return;
	}
	hanoi(n - 1, from, to, aux, need);
	step++;
	if (need == step) {
		printf("%d个盘子的汉诺塔问题，第%d步的移动轨迹是：%c--->%c\n", num,need, from, to);
	}
	hanoi(n - 1, aux, from, to, need);
}

int main(void) {
	int n = 0;
	printf("请指定盘子个数：\n");
	scanf("%d", &n);
	num = n;
	int m = 0;
	printf("请指定整数m:\n");
	scanf("%d", &m);
	int need = m+1;
	hanoi(n, 'A', 'B', 'C', need);
}
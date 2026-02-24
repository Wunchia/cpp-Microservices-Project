#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
bool is_leap_year(int year) {
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
		return true;
	}
	else {
		return false;
	}
}

int main(void) {
	int year;
	printf("请输入一个年份：\n");
	scanf("%d", &year);
	if (is_leap_year(year)) {
		printf("%d是闰年\n",year);
	}
	else {
		printf("%d是平年\n", year);
	}
	return 0;
}

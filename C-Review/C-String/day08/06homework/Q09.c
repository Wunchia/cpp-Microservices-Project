//定义一个枚举类型Month（别名），包含一年中12个月份的英文单词。并从一月份开始，为枚举成员分配一个从1开始的数字值。
//例如：JANUARY = 1，FEBRUARY = 2，依此类推....
//编写一个函数，接收Month类型的参数，返回该月份有多少天。

//注意：
//不考虑平年闰年，2月份一律输出28天。
//不要把12个case分支做12个处理，那也太笨了！
//枚举值应当采用英文单词字母全部大写的命名风格，类似宏定义。

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

enum Month {
	JANUARY = 1,
	FEBRUARY,
	MARCH,
	APRIL,
	MAY,
	JUNE,
	JULY,
	AUGUST,
	SEPTEMBER,
	OCTOBER,
	NOVEMBER,
	DECEMBER
};

int days_of_month(Month) {
	if (Month == 4 || 6 == Month || 9 == Month || 11 == Month) {
		return 30;
	}
	else if (Month == 2) {
		return 28;
	}
	else {
		return 31;
	}
}

int main() {
	int mon;
	printf("请输入月数：\n");
	scanf("%d", &mon);
	int days = days_of_month(mon);
	printf("%d 月的天数有 %d 天\n", mon, days);
	return 0;
}
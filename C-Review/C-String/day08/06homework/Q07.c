//定义一个Date结构体，包含年、月、日数据项。编写一个函数，计算两个日期之间的天数差。
//不考虑平年闰年，不考虑月份天数不同。
//假设每个月都是30天，每年是360天，以简化计算。

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct date {
	int year;
	int month;
	int day;
}Date;

int sub_date(Date d1, Date d2) {
	int year_d=0;
	int mon_d = 0;
	int day_d = 0;
	if (d1.year > d2.year) {
		year_d = d1.year - d2.year - 1;
		mon_d = 12 - d2.month-1+d1.month;
		day_d = 30 - d2.day+d1.day;
	}
	else if (d1.year < d2.year) {
		year_d = d2.year - d1.year - 1;
		mon_d = 12 - d1.month - 1+d2.month;
		day_d = 30 - d1.day+d2.day;
	}
	else {
		if (d1.month > d2.month) {
			mon_d = d1.month - d2.month - 1;
			day_d = 30 - d2.day+d1.day;
		}
		else if (d1.month < d2.month) {
			mon_d = d2.month - d1.month - 1;
			day_d = 30 - d1.day + d2.day;
		}
		else {
			if (d1.day > d2.day) {
				day_d = d1.day - d2.day;
			}
			else {
				day_d = d2.day - d1.day;
			}
		}
	}
	return year_d * 360 + mon_d * 30 + day_d;
}


int main(void) {

	Date d1 = { 2026,1,26 };
	Date d2 = { 2026,11,28 };
	int d = sub_date(d1,d2);
	printf("%d\n", d);

	return 0;
}
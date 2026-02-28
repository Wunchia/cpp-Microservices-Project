//基于以下函数声明，实现函数：
//void split_time(long total_sec, int* hour, int* minute, int* second);
//形参中的 total_sec 表示从凌晨00 : 00 : 00开始，到现在时间的秒数。
//请将 total_sec 转化以时(0 - 23)、分(0 - 59)、秒(0 - 59)表示的时间，并存放到函数外部由指针 hour, minute, second 指向的变量中。
//并在函数调用的位置，打印出当前的时间。

//测试用例：
//total_sec = 0，表示时间 00:00 : 00
//total_sec = 9527，表示时间 02 : 38 : 47
//total_sec = 3001，表示时间 00 : 50 : 01

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void split_time(long total_sec, int* hour, int* minute, int* second) {
	*hour = total_sec / 3600;
	*minute = total_sec / 60 % 60;
	*second = total_sec % 60;
}

int main(void) {
	long total_sec = 3001;
	int hour = 0, minute = 0, second = 0;
	split_time(total_sec, &hour, &minute, &second);
	printf("total_sec=%ld,表示时间 %02d : %02d : %02d\n", total_sec, hour, minute, second);
	return 0;
}
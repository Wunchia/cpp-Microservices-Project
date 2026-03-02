//请编写函数，将字符串中的字母和数字分开，使得字符串中前一部分是数字，后一部分是字母。
//void seperate(char* str);
//输入: "h1ell2o3"
//结果 : "123hello"或者任意数字在前，字母在后的字符串
//注意：要求字符串只包含字母和数字，字符串的长度不超过100，且分组要最终在原数组上完成。
//提供几个参考的实现思路：
//1.临时数组法。用两个临时数组一个装数字，一个装字母，然后再将数据合并回原数组。
//2.双指针夹逼交换法。两个指针向中间逼近，一个找字母一个找数字，找到后交换，直到两个指针相遇。
//3.双指针单向分区交换法。
//一个指针p用于遍历字符串，另一个指针p_num从头开始向后移动，用于标记下一个数字应该插入的位置。
//p指针每发现一个数字，就把它交换到p_num位置，然后p_num指针后移。
//直到遍历完字符串，所有的数字都会被交换到前面，所有字母都会被交换到后面。

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void swap(char* str, int a, int b) {
	char temp = str[a];
	str[a] = str[b];
	str[b] = temp;
}

void seperate(char* str) {
	int front = 0, end = 0;
	while (str[end + 1] != '\0') {
		end++;
	}
	while (front < end) {
		if ((str[front] >= 'a' && str[front] <= 'z') || (str[front] >= 'A' && str[front] <= 'Z')) {
			swap(str,front, end);
			end--;
		}
		else if (str[front] >= '0' && str[front] <= '9') {
			front++;
		}
		if ((str[end] >= 'a' && str[end] <= 'z') || (str[end] >= 'A' && str[end] <= 'Z')) {
			end--;
		}
		else if (str[end] >= '0' && str[end] <= '9') {
			swap(str, front, end);
			front++;
		}
	}
}

void print_str(char* str) {
	int i = 0;
	while (str[i] != '\0') {
		printf("%c", str[i++]);
	}
	printf("\n");
}

int main(void) {
	char str[] = "h1ell2o3";
	print_str(str);
	seperate(str);
	print_str(str);
	return 0;
}
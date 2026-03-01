#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
//给定一个整数数组，请将所有非正数(包含负数和0)全部移到数组开头，正数则全部移到数组末尾，要求原地完成，不使用额外内存空间。
//比如：
//数组[1, -2, 3, 0, -9, 0, 10, 3]
//最终分组完成后的效果应该是[非正数（包含0）, 正数]（稳定性不做要求）
//提示：仍然可以基于双指针单向分区或夹逼法求解。

void positive_end(int* arr, int len) {
	int *front = &arr[0];
	int *end = &arr[len - 1];
	while (front<end) {
		while (front<end&&(*front <= 0)) {
			front++;
		}
		while (front<end&&(*end > 0)) {
			end--;
		}
		int temp = *front;
		*front = *end;
		*end = temp;
	}
}

void print_arr(int* arr, int len) {
	for (int i = 0; i < len; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

int main() {
	int arr[5] = { 5,0,7,-1,-2 };
	print_arr(arr, 5);
	positive_end(arr, 5);
	print_arr(arr, 5);
	return 0;
}
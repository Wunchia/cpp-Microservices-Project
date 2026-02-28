//编写函数，查找一个int数组中的最大元素和第二大元素，并将它们分别存放在由 largest 和 second_largest 指向的变量中。
//
//按照下面的函数声明来实现这个函数。
//
//void find_two_largest(int arr[], int n, int* largest, int* second_largest);
//注意：为了简化实现，数组不存在重复元素，请不要考虑存在重复元素的情况。

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void find_two_largest(int arr[], int n, int* largest, int* second_largest) {
	int max1 = arr[0];
	int max2 = arr[0];
	for (int i = 0; i < n; i++) {
		if (arr[i] > max1) {
			max2 = max1;
			max1 = arr[i];
		}
		else if (arr[i] > max2) {
			max2 = arr[i];
		}
	}
	*largest = max1;
	*second_largest = max2;
}

int main(void) {
	int arr[5]={1, 8, 6, 9, 5};
	int max1 = 0, max2 = 0;
	find_two_largest(arr, 5, &max1, &max2);
	printf("数组中第一大的数是：%d,第二大的数是：%d\n", max1, max2);
	return 0;
}
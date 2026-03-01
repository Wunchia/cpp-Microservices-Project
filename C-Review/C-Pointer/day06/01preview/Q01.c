#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

//给定两个有序的整数子数组，然后将它们合并到一个足够长的新数组中，合并后的结果数组也应当是有序的。比如：
//数组1：[1, 3, 5, 6, 7]
//数组2：[2, 3, 4, 8]
//合并后的结果数组3：[1, 2, 3, 3, 4, 5, 6, 7, 8]
//提示：
//整个合并的过程类似"穿针引线"，利用两个索引逐一比较两个数组的元素大小，然后把较小元素放入数组3中。"穿针引线"结束，最终：
//一定会有一个数组元素被全部被赋值到数组3当中了。
//另一个数组元素一定还有剩余。
//那就把剩余数组的元素全部复制到数组3的后面即可。

int* merge_arr(int *arr1,int len1,int *arr2,int len2) {
	int i = 0, j = 0;
	int index = 0;
	int* arr = (int*)malloc(sizeof(int) * (len1 + len2));
	while (i < len1 && j < len2) {
		if (arr1[i] <= arr2[j]) {
			arr[index++] = arr1[i++];
		}
		else {
			arr[index++] = arr2[j++];
		}
	}
	while (i < len1) {
		arr[index++] = arr1[i++];
	}
	while (j < len2) {
		arr[index++] = arr2[j++];
	}
	return arr;
}

int main(void) {
	int arr1[5] = { 1, 3, 5, 6, 7 };
	int arr2[4] = { 2, 3, 4, 8 };
	int* arr = merge_arr(arr1, 5, arr2, 4);
	for (int i = 0; i < 9; i++) {
		printf("%d", arr[i]);
	}
	printf("\n");

	return 0;
}
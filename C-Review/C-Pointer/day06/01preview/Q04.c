#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void thr_div(int* arr, int len) {
	int* negative=&arr[0];
	int* positive=&arr[len-1];
	int* zero=&arr[0];
	while (zero <= positive) {
		if (*zero < 0) {
			swap(zero, negative);
			zero++;
			negative++;
		}
		else if (*zero == 0) {
			zero++;
		}
		else if (*zero > 0) {
			swap(zero, positive);
			positive--;
		}
	}
}

void print_arr(int* arr, int len) {
	for (int i = 0; i < len; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

int main(void) {
	int arr[7] = { 3,0,-7,0,-3,5,0 };
	print_arr(arr, 7);
	thr_div(arr, 7);
	print_arr(arr, 7);
	return 0;
}
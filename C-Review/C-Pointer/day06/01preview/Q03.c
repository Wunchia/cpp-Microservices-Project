#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void swap(int *a,int*b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}


void dutch_flag(int *arr,int len) {
	int* front = &arr[0];
	int* mid = &arr[0];
	int* end = &arr[len - 1];
	while (mid < end) {
		if (*mid== 0) {
			swap(front, mid);
			front++;
			mid++;
		}else if (*mid == 2) {
			swap(mid, end);
			end--;
		}
		else if (*mid == 1) {
			mid++;
		}
	}
}

void print_arr(int* arr,int len) {
	for (int i = 0; i < len; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

int main() {
	int a[6] = { 2,1,0,1,2,0 };
	print_arr(a, 6);
	dutch_flag(a, 6);
	print_arr(a, 6);
	return 0;
}
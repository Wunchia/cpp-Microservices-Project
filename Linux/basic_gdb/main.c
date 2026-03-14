#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define ARR_LEN(arr) ((sizeof(arr)) / sizeof(arr[0]))

void print_arr(int arr[]) {
	int len = ARR_LEN(arr);
	int num1 = *arr;
	int num2 = *(arr + 1);
	for (int i = 0; i < len; i++) {
		printf("%d======\n", arr[i]);
	}
}


int main(void) {

	int arr[] = { 10,20,30,40,50,60 };
	for (int i = 0; i < ARR_LEN(arr); i++) {
		printf("%d-----\n", arr[i]);
	}

	print_arr(arr);
	return 0;
}
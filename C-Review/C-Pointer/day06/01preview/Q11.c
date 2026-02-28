#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//第一题：
//查找数组的最大值和最小值，但要将最大值作为返回值返回，最小值则依靠传入的指针完成赋值。
//要求不能使用"[]"运算符。
//函数的声明如下：
//int max_min(int* arr, int len, int* pmin);

int find_max_min(int* arr, int len, int* min) {
	*min = *arr;
	int max = *arr;
	for (int i = 0; i < len; i++) {
		if (*min > *(arr+i)) {
			*min = *(arr + i);
		}
		if (max < *(arr + i)) {
			max = *(arr + i);
		}
	}
	return max;
}

//第二题：
//求平均值，给定一个double数组，求平均值，并且返回。
//要求使用while循环遍历数组，然后配合"*p++"的语法实现。
//函数的声明如下：
//double get_ave(double* arr, int len);

double get_ave(double* arr, int len) {
	int i = 0;
	double sum = 0;
	double *p = arr;
	while (i++ < len) {
		sum += *p++;
	}
	return sum/(double)len;
}

int main() {
	int max = 0, min = 0;
	int arr1[5] = { 2,3,4,5,6 };
	double arr2[5] = { 2.0,3.0,4.0,5.0,6.0 };
	max = find_max_min(arr1, 5, &min);
	printf("arr的最大值是%d,最小值是%d\n", max, min);
	printf("arr的元素平均值为%.2lf\n", get_ave(arr2, 5));
	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int global_num = 999;
void test_global_in_test() {
	printf("test_global_in_test did\n");
	printf("global_num = %d in test.c\n", global_num);
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX_SIZE 10
//#define SQRT_DIFF(x,y) (x*x-y*y)
#define SQRT_DIFF(x,y) ((x)*(x)-(y)*(y))
/*

*/

int main(void) {
	printf("hello world!\n");
	printf("maxsize=%d\n", MAX_SIZE);
	printf("sqrt_diff=%d\n", SQRT_DIFF(5, 4));
	printf("sqrt_diff=%d\n", SQRT_DIFF(2 + 3, 4));
	return 0;
}
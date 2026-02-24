#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*

*/
void test1(void) {
	printf("here is the test1 function in main.c.\n");
}

void test2(void);

int main(void) {
    test1();
    test2();
    return 0;
}
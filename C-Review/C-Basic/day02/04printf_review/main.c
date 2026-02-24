#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*

*/
int main(void) {
    int ret1=printf("hello\n");
    printf("ret1=%d\n", ret1);
    int ret2 = printf("");
    printf("ret2=%d\n", ret2);
	printf("|%4f|\n", 3.14159f);
	printf("|%10f|\n", 3.14159f);
	printf("|%.4f|\n", 3.14159f);
	printf("|%10.1f|\n", 3.14159f);
	printf("|%010.1f|\n", 3.14159f);
	printf("|% 4.1f|\n", 3.14159f);
	printf("|%-10.1f|\n", 3.14159f);
	printf("|%+10.1f|\n", 3.14159f);
    return 0;
}
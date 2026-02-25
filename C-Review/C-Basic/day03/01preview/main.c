#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*

*/
int main(void) {
	int width = 10;
    int point = 2;
	float value = 123.456789f;
    printf("%*.*f\n",width,point,value);
    unsigned int small_val = 4294967295; // 接近 32 位无符号数的极限
    size_t large_val = 4294967296ULL;    // 超过 32 位，达到 64 位级别
    unsigned int cmpare_val = 4294967296;
    printf("使用 unsigned int 打印: %u\n", small_val);
    printf("使用 unsigned int 打印: %u\n", cmpare_val);//溢出
    // 注意：如果在 32 位系统上，下面这行可能会溢出；
    // 但在 64 位系统上，size_t 能轻松处理。
    printf("使用 size_t (%%zu) 打印: %zu\n", large_val);
    int i, j;
    scanf("%d/%d", &i, &j);//输入5(空格)/(空格)96 j无法正确读入96
    scanf("%d / %d", &i, &j);//输入5(空格)/(空格)96 j可以正确读入96
	printf("%d,%d\n", i, j);
    return 0;
}
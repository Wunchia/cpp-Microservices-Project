#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*

*/

int gcd(int a,int b) {
    //求最大公约数
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void simplify(int *a, int *b) {
    int divisor = gcd(*a, *b);
    *a /= divisor;
    *b /= divisor;
}

int main(void) {
    int numerator1, denominator1;
	int numerator2, denominator2;
    printf("请输入第一个分数（分子/分母）");
    scanf("%d/%d", &numerator1,&denominator1);
    printf("请输入第二个分数（分子/分母）");
    scanf("%d/%d", &numerator2, &denominator2);
    int result_numerator = numerator1 * denominator2 + numerator2 * denominator1;
    int result_denominator=denominator1*denominator2;
    printf("两个分数的和是一个分数，即：%d/%d\n",result_numerator,result_denominator);
    simplify(&result_numerator, &result_denominator);
    if (result_numerator%result_denominator==0) {
        printf("两个分数的和是一个整数，即%d\n", result_numerator / result_denominator);
    }
    else {
        printf("两个分数的和是一个分数，即：%d/%d\n", result_numerator, result_denominator);
    }
    return 0;
}
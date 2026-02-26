#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
/*

*/
int main(void) {
    int start_rate = 0;
    int years = 0;
    printf("请输入年利率：\n");
    scanf("%d", &start_rate);
    while (getchar() != '\n');
    printf("请输入要投资的年份：\n");
    scanf("%d", &years);
    while (getchar() != '\n');

    int fund = 100;
    double (*rate)[5] = (double(*)[5])malloc(sizeof(double) * 5 * years);
    for (int i = 0; i < years; i++) {
        for (int j = 0; j < 5; j++) {   
            rate[i][j] = fund * pow((1+(start_rate+j)/100.0), i+1);
        }
    }

    printf("%-8s","yesrs");
    for (int i = 0; i < 5; i++) {
        printf("%7d%%", start_rate+i);
    }
    printf("\n");
    for (int i = 0; i < years; i++) {
        printf("%-6d\t", i + 1);
        for (int j = 0; j < 5; j++) {
            printf("%8.2lf", rate[i][j]);
        }
        printf("\n");
    }

    return 0;
}
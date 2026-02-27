#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
/*

*/

bool is_triangle(int a, int b, int c) {
    if (a + b > c && a + c > b && b + c > a) {
        return true;
    }
    else {
        return false;
    }
}

double get_area(int a, int b, int c) {
    double p = (a + b + c) / 2.0;
	double area = sqrt(p * (p - a) * (p - b) * (p - c));
    return area;
}

int main(void) {
    printf("请输入三角形的三条边长：\n");
    int a = 0, b = 0, c = 0;
    scanf("%d %d %d", &a, &b, &c);
    if (is_triangle(a, b, c)) {
        printf("三条边长可以构成三角形\n");
        printf("三角形的面积为：%.2lf\n", get_area(a, b, c));
    }
    else {
        printf("三条边长不能构成三角形\n");
    }
    return 0;
}
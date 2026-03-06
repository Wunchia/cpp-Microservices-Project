#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*

*/
typedef double (*op)(double, double);

double add(double a, double b) {
    return a + b;
}

double sub(double a, double b) {
    return a - b;
}

double mul(double a, double b) {
    return a * b;
}

double div(double a, double b) {
    return a / b;
}


double cal(double a, double b, op op) {
    return op(a, b);
}

int main(void) {
    double a = 3.0, b = 5.0;
    printf("solution = %.2lf\n", cal(a, b, add));
    printf("solution = %.2lf\n", cal(a, b, sub));
    printf("solution = %.2lf\n", cal(a, b, mul));
    printf("solution = %.2lf\n", cal(a, b, div));
    return 0;
}
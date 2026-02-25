#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
typedef int DataType;
/*

*/
void test01() {
    int int1 = 10;
    long long1 = 20L;
    long long longlong1 = 30LL;

    float f1 = 30.14f;
    double d1 = 3.333;
    printf("%d\n", sizeof(int1 + long1));
    printf("%d\n", sizeof(long1 + long1));
	printf("%d\n", sizeof(long1 + longlong1));
    printf("%d\n", sizeof(f1 + longlong1));
    printf("%d\n", sizeof(f1 + d1));
    printf("%d\n", sizeof(d1 + longlong1));
}

void test02() {
    int num1 = 10;
    short s1 = (short)num1;
    printf("%d\n", sizeof(num1));
    printf("%d\n", sizeof(s1));
}

void test03() {
    DataType data = 10;
    printf("%d\n", data);
    printf("sizeof int8_t=%d\n",sizeof(int8_t));
    printf("sizeof int16_t=%d\n",sizeof(int16_t));
    printf("sizeof int32_t=%d\n",sizeof(int32_t));
    printf("sizeof uint32_t=%d\n",sizeof(uint32_t));
}

void test04() {
    int num1 = 56;
    int num2 = 46;

    // num1 & num2
    // 0011 1000   ==== 56
    // 0010 1110   ==== 46
    // 0010 1000   ==== 8+32===40

    // num1 | num2
    // 0011 1000   ==== 56
    // 0010 1110   ==== 46
    // 0011 1110   ==== 2+4+8+16+32 = 62

    // num1 ^ num2
    // 0011 1000   ==== 56
    // 0010 1110   ==== 46
    // 0001 0110 === 2+4+16=22

    printf("%d\n", (num1 & num2));
    printf("%d\n", (num1 | num2));
    printf("%d\n", (num1 ^ num2));
}

bool is_power_2(int n) {
    //    n=0010 1000  -->40
    //则n-1=0010 0110
    // n&(n-1)=0010 0000 !=0
    //      n=1000   -->8
    //  则n-1=0111
    //n&(n-1)=0000 =0
    return (n & (n - 1)) == 0;
}

int find_last_set_bit(int n) {
    return n & (-n);
    //补码 全部取反 末位+1
    //从而只有原数的最后一个1在补码的对应位置也是1
    //相与后只有该位为1 输出自然为对应数值
}

void test_c1() {
    char ch;
    while ((ch = getchar()) != '\n') {
        printf("========%c\n", ch);
    }
}

void test_c2() {
    /*char c;
    while ((c = getchar()) == '\n');*/
    for (char ch;;) {
        ch = getchar();
        if (ch == '\n') {
            break;
        }
        printf("--------%c\n", ch);
    }
}

int main(void) {
   /* test01();
    int a = 10.1;
    char b = 97.9f;
    double c = 0.1;
    float d = c;
    printf("size of a =%d\n", sizeof(a));
    printf("size of b =%d\n", sizeof(b));
    printf("size of c =%d\n", sizeof(c));
    printf("size of d =%d\n", sizeof(d));
    printf("a=%d,b=%c,c=%lf,d=%f\n", a, b, c, d);*/
    //test02();
    //test03();
    //test04();
    /*int n = 0;
    scanf("%d", &n);
    if (is_power_2(n)) {
        printf("%d是2的幂\n", n);
    }
    else {
        printf("%d不是2的幂\n",n);
    }

    printf("%d的最后一比特所在位置为：%d\n",n,find_last_set_bit(n));*/
    test_c1();
    test_c2();

    return 0;
}
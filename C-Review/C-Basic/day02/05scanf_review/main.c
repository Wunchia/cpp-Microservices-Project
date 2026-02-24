#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
void test01() {
	//scanf的返回值是成功匹配的个数
	int num1, num2;
	int ret = scanf("%d %d", &num1, &num2);
	printf("%d\n", ret);
}
void test02() {
	int num1 = 9999;
	double d1 = 3.1515;
	scanf("%d %lf", &num1, &d1);
	printf("num1=%d\nd1=%lf\n", num1, d1);
}
void test03() {
	int num1 = 0, num2 = 0;
	scanf("%d %d", &num1, &num2);
	printf("num1=%d,num2=%d\n", num1, num2);
}
void test04() {
	int num1 = 111;
	int num2 = 222;
	printf("%d %d\n", num1, num2);
	printf("%d %d\n", &num1, &num2);
}
void test05() {
	int num1 = 10;
	char ch = 'z';
	scanf("%d", &num1);
	scanf(" %c", &ch);
	printf("num1=%d,ch=%c\n", num1, ch);
}
int main() {
	//test01();
	//test02();
	//test03();
	//test04();
	test05();
	return 0;
}
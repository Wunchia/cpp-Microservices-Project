#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
//有三根杆子A，B，C。A杆上有 N 个(N > 1) 穿孔圆盘，盘的尺寸由下到上依次变小。要求按下列规则将所有圆盘移至 C 杆：
//每次只能移动一个圆盘;
//大盘不能叠在小盘上面。
//利用递归的方式，打印出移动轨迹。运行结果如下图所示 :

void hanoi(int n,char from, char aux, char to) {
	if (n == 1) {
		printf("%c--->%c\n",from,to);
		return;
	}
	hanoi(n - 1, from, to, aux);
	printf("%c--->%c\n",from,to);
	hanoi(n-1,aux,from,to);
}

int main() {
	int n = 4;
	printf("完成%d个盘子的汉诺塔问题，全部移动轨迹如下：\n", n);
	hanoi(n, 'A', 'B', 'C');
	return 0;
}
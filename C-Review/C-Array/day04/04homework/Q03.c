#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
/*
编写一个程序，要求用户键盘录入十名学生的语文成绩(百分制)，然后存储在一个一维数组中。最后计算全班的平均成绩、最高分和最低分，并打印出来。

注意：

1.要求使用一个int数组来存放成绩，平均成绩保留2位小数。

2.如果你还不理解将数组作为参数传递的话，请不要提取函数，直接将所有代码写到main函数里。
*/
double cal_average(int score[],int len,int *max,int *min) {
    double sum = 0;
    *max = -1; *min = 101;
    for(int i = 0; i < len; i++) {
        if (score[i] < *min) {
            *min = score[i];
        }
        if (score[i] > *max) {
            *max = score[i];
        }
        sum += score[i];
    }
    return sum / len;
}

int main(void) {
    int score[10] = { 0 };
	printf("请输入10名学生的语文成绩：\n");
	for (int i = 0; i < 10; i++) {
        scanf("%d", &score[i]);
    }
    int max, min;
    double average=cal_average(score, 10, &max, &min);
    printf("平均分：%.2lf  最高分：%d   最低分：%d\n", average, max, min);

    return 0;
}
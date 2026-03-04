#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
//第一题：
//下面结构体类型的变量的内存布局是怎样的？请使用VS的Debug模式查看它的内存布局

typedef struct stundent_s {
	int number;
	char name[25];
	char gender;
	int chinese;
	int math;
	int english;
} Student;

//// 结构体对象的声明和初始化
//Student s1 = { 1, "Jack", 'm', 100, 100, 100 };
//要求：截图展示内存窗口中的对齐填充，然后提交截图。
//
//第二题：
//基于上述的结构体类型的定义，实现以下功能：
//1.从键盘输入5个学生的信息，将这些同学的信息采用结构体数组的方式存储起来。（代码直接写在main函数里）
//2.编写一个函数，用于打印单个结构体信息。然后在main函数里调用该函数，打印这个结构体数组。
//3.编写一个函数，用于求三个学科的平均分。然后在main函数里调用该函数，打印这三个学科的平均分。

void input_stu(Student* s) {
	printf("请输入：学号 姓名 性别 语文成绩 数学成绩 英语成绩\n");
	scanf("%d %s %c %d %d %d", &s->number, &s->name, &s->gender, &s->chinese, &s->math, &s->english);
}

void print_stu(Student* s) {
	printf("学号:%d 姓名:%s 性别:%c 语文成绩:%d 数学成绩:%d 英语成绩:%d\n", s->number, s->name, s->gender, s->chinese, s->math, s->english);
}

void count_average(Student* s) {
	double average = (s->chinese+s->math+s->english)/3.0;
	printf("%s 同学的三科平均分是：%.2lf\n", s->name, average);
}

int main(void) {
	//Student s1 = { 1024,"xiaoming",'m',64,64,64 };
	Student s1 = { 0000,"none",'n',0,0,0 }, s2 = { 0000,"none",'n',0,0,0 }, s3 = { 0000,"none",'n',0,0,0 }, s4 = { 0000,"none",'n',0,0,0 }, s5 = { 0000,"none",'n',0,0,0 };
	Student stu[5] = {s1,s2,s3,s4,s5};
	for (int i = 0; i < 5; i++) {
		input_stu(&stu[i]);
	}
	printf("============\n");
	for(int i=0;i<5;i++){
		print_stu(&stu[i]);
		count_average(&stu[i]);
		printf("\n");
	}

	return 0;
}
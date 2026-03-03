#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*

*/

typedef struct student {
    int num;
    char name[20];
    char gender[10];
    int age;
    double score;
}Student;

void test01(Student s1) {
    printf("id=%d,name=%s,gender=%s,age=%d,score=%.2lf\n", s1.num, s1.name, s1.gender, s1.age, s1.score);
    s1.num = 9999;
    printf("in test : id=%d,name=%s,gender=%s,age=%d,score=%.2lf\n", s1.num, s1.name, s1.gender, s1.age, s1.score);
}

void test02(Student *s1) {
    printf("id=%d,name=%s,gender=%s,age=%d,score=%.2lf\n", s1->num, s1->name, s1->gender, s1->age, s1->score);
    s1->num = 9999;
    printf("in test : id=%d,name=%s,gender=%s,age=%d,score=%.2lf\n", s1->num, s1->name, s1->gender, s1->age, s1->score);
}

int main(void) {
    Student s1 = {1001,"Alice","Female",21,99};
    struct student s2 ={1002,"Tom" };

    printf("id=%d,name=%s,gender=%s,age=%d,score=%.2lf\n", s1.num, s1.name, s1.gender, s1.age, s1.score);
    printf("id=%d,name=%s,gender=%s,age=%d,score=%.2lf\n", s2.num, s2.name, s2.gender, s2.age, s2.score);
    //成员对齐+整体对齐
    //48  4+20+10+4+8=46 double大小的倍数-->8*6=48
    //结构体的总大小必须是其最大基本类型成员（这里是 double score，占 8 字节）大小的倍数
    printf("size of student=%d\n", sizeof(Student));

    s1 = s2;//位拷贝
    //这行代码执行后，编译器会生成指令
    //将 s2 所占用的那块内存空间中的每一个位，原封不动地拷贝到 s1 对应的内存空间里
    printf("id=%d,name=%s,gender=%s,age=%d,score=%.2lf\n", s1.num, s1.name, s1.gender, s1.age, s1.score);
    printf("id=%d,name=%s,gender=%s,age=%d,score=%.2lf\n", s2.num, s2.name, s2.gender, s2.age, s2.score);

    s1.num = 6666;
    printf("id=%d,name=%s,gender=%s,age=%d,score=%.2lf\n", s1.num, s1.name, s1.gender, s1.age, s1.score);
    printf("id=%d,name=%s,gender=%s,age=%d,score=%.2lf\n", s2.num, s2.name, s2.gender, s2.age, s2.score);
    test01(s1);//结构体也是值传递
    printf("after test : id=%d,name=%s,gender=%s,age=%d,score=%.2lf\n", s1.num, s1.name, s1.gender, s1.age, s1.score);

    Student* ps1 = &s1;
    //结构体变量用.
    // 结构体指针用->
    //ps1->是语法糖，相当于(*ps1).
    printf("id = % d, name = % s, gender = % s, age = % d, score = % .2lf\n", ps1->num, (*ps1).name, ps1->gender, ps1->age, ps1->score);
    test02(ps1);
    printf("after test : id=%d,name=%s,gender=%s,age=%d,score=%.2lf\n", ps1->num, (*ps1).name, ps1->gender, ps1->age, ps1->score);

    return 0;
}
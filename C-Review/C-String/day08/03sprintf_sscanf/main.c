#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*

*/

void test01() {
    int num1 = 10;
    double d1 = 3.14;
    printf("%d========%lf\n", num1, d1);
    char buf[50] = { 0 };
    sprintf(buf, "%d==+==%lf\n", num1, d1);//输出到字符串buf
    printf("%s\n", buf);//输出到屏幕
}

void test02() {
    int num = 0;
    double d1 = 0.0;
    scanf("%d%lf", &num, &d1);
    printf("%d===%lf\n", num, d1);
    char buf[20] = "666 3.14";
    sscanf(buf, "%d %lf", &num, &d1);
    printf("%d==+==%lf\n", num, d1);
}

int main(int argc,char* argv[]) {
    //test01();
    //test02();
    int num = 0;
    sscanf(argv[1], "%d", &num);
    printf("num=%d\n", num);
    for (int i = 0; i < num; i++) {
        printf("====\n");
    }
    //在命令行输入以下命令执行此程序
    // 直接在vs点运行会debug assertion failed（运行时断言失败）
    //\Users\Wunchia\source\repos\cpp-Microservices-Project\C-Review\C-String\day08\x64\Debug> ./03sprintf_sscanf.exe 5
    return 0;
}
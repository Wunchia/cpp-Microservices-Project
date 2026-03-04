//请你通过命令行参数传递额外的三个参数：
//10 8.8 hello
//其含义如下：
//第一个额外命令行参数10：整数10
//第二个额外命令行参数8.8：浮点数8.8
//第三个额外命令行参数hello：就是字符串hello
//关于如何传递命令行参数，在Windows环境下可以有两种选择：
//直接在集成开发环境VS当中传递命令行参数。
//在Windows的命令行，也就是CMD黑窗口中启动程序，传递命令行参数。
//关于这两种方式，具体如何来完成，请参考文档：《字符串》当中的《命令行参数》小节。
//请你完成下面的操作：
//题目一：
//先输出一下当前命令行参数的个数，再循环打印一下命令行参数字符串数组，输出的格式你可以自己来决定。

//题目二：
//使用sscanf函数将两个额外的命令行参数，转换成它们对应的基本数据类型（int和double）。

//题目三：
//在完成前两个命令行参数的类型转换后，请计算它们之和。
//然后利用sprintf函数，加上最后一个命令行参数字符串，按照下面的格式来构建字符串并输出到字符数组中：
//"10 + 8.8 = 18.80hello"
//最后打印这个字符数组表示的字符串。
//一个参考的代码输出如下图所示：

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char*argv[]) {
	printf("now argc = %d\n", argc);
	for (int i = 0; i < argc; i++) {
		printf("argv[%d]=%s\n", i, argv[i]);
	}
	int buf01 = 0;
	double buf02 = 0.0;
	char buf03[20] = {0};
	sscanf(argv[1],"%d", &buf01);
	sscanf(argv[2], "%lf", &buf02);
	sscanf(argv[3], "%s", &buf03 );
	printf("%d + %lf = %lf%s\n", buf01, buf02, buf01 + buf02, buf03);

	return 0;
}
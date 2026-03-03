//编写一个函数，计算一个字符串中单词的数量。这里，单词被定义为由空格分隔的字符序列。
//例如，对于字符串"hello world! word Excel space blank"
//就应该输出有6个单词
//注意：空格可能连续出现。

//思路参考 :
//1.整个过程就是跳过前面的所有空白字符，先找到一个非空字符，然后再跳过所有非空字符找到一个空白字符，于是确定找到一个单词。
//2.第二种思路 : 遍历整个字符串，如果字符是非空格制表符，那么就是单词的一部分，继续遍历直到碰到空字符或者空格制表符，意味着单词结束，计数器加1
//两种思路皆可。

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int count_words(char* str) {
	int i = 0;
	int count = 0;
	int flag = 1;
	while (str[i] != '\0') {
		if (str[i] == ' ') {
			flag = 1;
			i++;
			continue;
		}
		else {
			if (((str[i]>='a'&&str[i]<='z')||(str[i] >= 'A' && str[i] <= 'Z'))&&flag == 1) {
				count++;
			}
			flag = 0;
		}

		i++;
	}
	return count;
}

int main() {
	char str[] = "hello world! word Excel space blank";
	int count = count_words(str);
	printf("共计有%d个单词\n", count);
	return 0;
}
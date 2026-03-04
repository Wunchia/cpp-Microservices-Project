//标准库函数strcat会将一个字符串追加到另一个字符串的末尾。
//现在我们编写一个函数把两个字符串拼接起来，返回拼接的结果，但要求不改变其中任何一个字符串。其函数声明如下：
//char* my_strcat(const char* prefix, const char* suffix);
//形参prefix表示前缀，suffix表示后缀，拼接的结果是prefix + suffix
//比如：my_strcat("abc", "d")，拼接的结果是"abcd"。

//思路：
//在堆上分配内存空间，用于存储结果字符串。
//将prefix和suffix两个字符串的字符信息复制进去。

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

char* my_strcat(const char* prefix, const char* suffix) {
	int len = 0;
	char* cur_prefix=prefix;
	char* cur_suffix = suffix;
	while (*cur_prefix != '\0') {
		len++;
		cur_prefix++;
	}
	while (*cur_suffix != '\0') {
		len++;
		cur_suffix++;
	}
	char* ret = (char*)malloc(sizeof(char) * (len+1));
	if (ret == NULL) {
		printf("my_strcat malloc failed.\n");
		return NULL;
	}
	cur_prefix = prefix;
	cur_suffix = suffix;
	int i = 0;
	while (*cur_prefix != '\0') {
		ret[i] = *cur_prefix++;
		i++;
	}
	while (*cur_suffix != '\0') {
		ret[i] = *cur_suffix++;
		i++;
	}
	ret[i] = '\0';
	return ret;
}

int main(void) {
	char a[] = "abc";
	char b[] = "defg";
	char* p = my_strcat(a, b);
	if (p == NULL) {
		printf("main get my_strcat failed.\n");
		return -1;
	}
	printf("%s\n", p);
	free(p);
	return 0;
}
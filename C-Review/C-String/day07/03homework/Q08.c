#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//依照C语言的字符串标准库函数，手动实现以下函数：
//size_t my_strlen(const char* str);
//char* my_strcpy(char* dest, const char* src);
//char* my_strncpy(char* dest, const char* src, size_t n);
//char* my_strcat(char* dest, const char* src);
//char* my_strncat(char* dest, const char* src, size_t n);
//int my_strcmp(const char* str1, const char* str2);
//函数的实现要模拟标准库函数中对应函数的行为，不要依据自己的理解来实现这些函数。

size_t my_strlen(const char* str) {
	char* p = str;
	while (*str != '\0') {
		str++;
	}
	return str - p;
}

char* my_strcpy(char* dest, const char* stc) {
	char* p = dest;
	while (*stc != '\0') {
		*dest++ = *stc++;
	}
	if (*stc == '\0') {
		*dest = '\0';
	}
	return p;
}

char* my_strncpy(char* dest, const char* src, size_t n) {
	int i = 0;
	char* p = dest;
	if (n < strlen(src) + 1) {
		while (i <= n) {
			*dest++ = *src++;
			i++;
		}
		*dest = '\0';
	}
	else if (n == strlen(src) + 1) {
		while (i <= n) {
			dest[i] = src[i];
			i++;
		}
	}
	else {
		while (*src != '\0') {
			*dest++ = *src++;
			n--;
		}
		while (n > 0) {
			*dest++ = '\0';
			n--;
		}
	}
	return p;
}

char* my_strcat(char* dest, const char* src) {
	char* p = dest;
	while (*dest != '\0') {
		dest++;
	}
	while (*src != '\0') {
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return p;
}

char* my_strncat(char* dest, const char* src, size_t n) {
	char* p = dest;
	while (*dest != '\0') {
		dest++;
	}
	int i = 0;
	while (i < n && *src != '\0') {
		*dest = *src;
		dest++;
		src++;
		i++;
	}
	*dest = '\0';
	return p;
}

int my_strcmp(const char* str1, const char* str2) {
	while (*str1 != '\0' && *str2 != '\0') {
		if (*str1 - *str2 != 0) {
			return *str1 - *str2;
		}
		str1++;
		str2++;
	}
	return *str1 - *str2;
}

int main(void) {
	char str1[] = "hello world!";
	char str2[] = "hello world!";
	char str3[] = "abcde abcde?";
	char str4[50] = "abcde abcde?";

	printf("len of str = %d\n", my_strlen(str1));
	printf("str1=%s\n", str1);
	printf("str2=%s\n", str2);
	printf("str3=%s\n", str3);
	printf("str4=%s\n", str4);
	printf("copy 2 to 3 ,str3=%s\n", my_strcpy(str3, str2));
	printf("copy 4 to 3 ,str3=%s\n", my_strncpy(str3, str4,5));
	printf("cat 2 to 4 ,str4=%s\n", my_strcat(str4, str2));
	printf("cat 3 to 4 ,str4=%s\n", my_strncat(str4, str3,5));

	if (0==my_strcmp(str1, str2)) {
		printf("str1与str2相同\n");
	}

	return 0;
}
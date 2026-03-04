//依照C语言的字符串标准库函数，手动实现以下函数：
//size_t my_strlen(const char* str);
//char* my_strcpy(char* dest, const char* src);
//char* my_strncpy(char* dest, const char* src, size_t n);
//char* my_strcat(char* dest, const char* src);
//char* my_strncat(char* dest, const char* src, size_t n);
//int my_strcmp(const char* str1, const char* str2);
//函数的实现要模拟标准库函数中对应函数的行为，不要依据自己的理解来实现这些函数。

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

size_t my_strlen(const char* str) {
	size_t i = 0;
	while (*str != '\0') {
		i++;
		str++;
	}
	return i;
}

char* my_strcpy(char* dest, const char* src) {
	char* cur_dest = dest;
	char* cur_src = src;
	while (*cur_src != '\0') {
		*cur_dest = *cur_src;
		cur_dest++;
		cur_src++;
	}
	*cur_dest = '\0';
	return dest;
}

char* my_strncpy(char* dest, const char* src, size_t n) {
	char* old_dest = dest;
	while (n > 0 && (*dest++ = *src++)) {
		n--;
	}
	while (n > 0){
		*dest++ = '\0';
		n--;
	}
	return old_dest;
}

char* my_strcat(char* dest, const char* src) {
	char* tmp_dest = dest;
	while (*dest != '\0') dest++; 
	while ((*dest++ = *src++) != '\0'); 
	return tmp_dest;
}

char* my_strncat(char* dest, const char* src, size_t n) {
	char* temp = dest;
	while (*dest!= '\0')dest++;
	while (*src != '\0'&&n>0) {
		*dest++ = *src++;
		n--;
	}
	*dest = '\0';
	return temp;
}

int my_strcmp(const char* str1, const char* str2) {
	while (*str1 == *str2&&*str1!='\0'&&*str2!='\0') {
		str1++;
		str2++;
	}
	return *(unsigned char*)str1 - *(unsigned char*)str2;;
}

int main(void) {

	return 0;
}
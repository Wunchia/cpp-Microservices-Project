#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//编写一个函数，检查给定的字符串中的圆括号()是否正确匹配。注意只考虑小括号，字符串中没有其它括号。
//如字符串：((Hello)(World))
//函数会返回一个布尔值，表示匹配成功或失败
//注意：只考虑英文小括号()，不需要考虑其它括号，更不需要考虑中文符号。

bool bracket_matching(char *str) {
	int i = 0, top = 0;
	char bracket_stack[10] = "";
	while (str[i] != '\0') {
		if (str[i] == '(') {
			bracket_stack[top] = '(';
			top++;
		}
		else if (str[i] == ')') {
			if (top == 0) {
				bracket_stack[top] = ')';
				top++;
			}
			if (bracket_stack[top - 1] == '(') {
				top--;
			}
			else {
				bracket_stack[top] = ')';
				top++;
			}
		}
		i++;
	}
	if (top == 0) {
		return true;
	}
	else {
		return false;
	}
}

int main(void) {
	char str[] = "((Hello)(World)))";
	bool is_matched = bracket_matching(str);
	if (is_matched) {
		printf("匹配成功");
	}
	else {
		printf("不匹配");
	}

	return 0;
}
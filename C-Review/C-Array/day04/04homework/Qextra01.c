//1.给一个字符数组，判断元音字母的个数。 aeiou
//2.给一个字符数组，将元音字母找到，拼接到这个数组的后面
//假设数组到了 0 这个字符，就结束了{ abcde0ae }
//3.给你一个字符数组，将其内容复制一份。 长度不会超过100
//4.比较两个字符数组内容是否完全相同
//5.统计一个字符数组中，字母的个数
//6.删除一个字符数组中的空格。abcde ccdde aab
//7.将一个字符数组中，大写字母转换为小写，小写转换为大写，数字不动。没有其他的

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int find_aeiou(char arr[],int len) {
	int count = 0;
	for (int i = 0; i < len; i++) {
		if(arr[i] == 'a' || arr[i] == 'e' || arr[i] == 'i' || arr[i] == 'o' || arr[i] == 'u') {
			count++;
			}
	}
	return count;
}

void append_aeiou(char arr[], int len) {
	int count = find_aeiou(arr, len);
	
}

int main() {

	return 0;
}

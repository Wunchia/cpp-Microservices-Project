#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void test() {
	FILE* fp = fopen("1.txt", "a");
	if (fp == NULL) {
		perror("1.txt");
		return;
	}
	
	char buf[20] = { 'a','k','4','7'};
	fputs(buf, fp);
	fseek(fp, 0, SEEK_SET);
	fclose(fp);
	fp = fopen("1.txt", "r");
	fgets(buf, 20, fp);
	printf("%s\n", buf);
}

int main() {
	test();
	return 0;
}
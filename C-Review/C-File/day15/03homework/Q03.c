#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

char* read_file(const char* path) {
	FILE* fp = fopen(path, "r");
	if (fp == NULL) {
		printf("open failed.\n");
		return NULL;
	}
	fseek(fp, 0, SEEK_END);
	long length=ftell(fp);
	rewind(fp);

	char* buffer = (char*)malloc(length+1);
	size_t index=fread(buffer, 1,length,fp);
	buffer[index] = '\0';

	fclose(fp);
	return buffer;
}

int main(void) {
	char* text = read_file("test.txt");
	if (text) {
		printf("%s\n", text);
	}
	free(text);
	return 0;
}
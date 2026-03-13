#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

typedef struct fileinfo {
	char filename[64];
	long filesize;
}FileInfo;

int main(void) {
	FileInfo f1 = { "filename",8 };
	FILE* fp = fopen("index.db", "wb");
	if (fp == NULL) {
		perror("index.db wb open filed");
		return -1;
	}
	fwrite(&f1,sizeof(FileInfo), 1, fp);
	fclose(fp);
	FileInfo f2;
	fp = fopen("index.db", "rb");
	if (fp == NULL) {
		perror("index.db rb open filed");
		return -1;
	}
	fread(&f2, sizeof(FileInfo), 1, fp);
	printf("%s---%ld\n", f2.filename,f2.filesize);
	
	fclose(fp);
	return 0;
}
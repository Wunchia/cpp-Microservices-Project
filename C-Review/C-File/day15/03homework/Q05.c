#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


int main(void) {
	FILE* fp1 = fopen("source.dat","rb");
	if (fp1 == NULL) {
		perror("source.dat");
		return -1;
	}
	FILE* fp2 = fopen("dest.dat", "wb");
	if (fp2 == NULL) {
		perror("dest.dat");
		fclose(fp1);
		return -1;
	}
	int ch;
	while ((ch = fgetc(fp1)) != EOF) {
		fputc(ch, fp2);
	}

	fclose(fp1);
	fclose(fp2);
	return 0;
}
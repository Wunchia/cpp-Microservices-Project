#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main(void) {

    const char* filename = "config.txt";
    const char* ip = "192.168.1.100";
    int port = 8080;

    FILE* fp_out = fopen(filename, "w");
    if (fp_out == NULL) {
        perror("写入文件打开失败");
        return -1;
    }
    
    fprintf(fp_out, "%s %d", ip, port);
    fclose(fp_out);

    char ip_read[64]; 
    int port_read;

    FILE* fp_in = fopen(filename, "r");
    if (fp_in == NULL) {
        perror("读取文件打开失败");
        return -1;
    }
    
    if (fscanf(fp_in, "%s %d", ip_read, &port_read) == 2) {
        printf("加载配置: IP=%s, Port=%d\n", ip_read, port_read);
    }
    fclose(fp_in);

	return 0;
}
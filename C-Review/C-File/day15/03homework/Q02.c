#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*

*/
void copy_file_char(const char* src_file, const char* dest_file) {
    FILE* fp1 = fopen(src_file, "r");
    if (fp1 == NULL) {
        printf("%s open failed.\n", src_file);
        return;
    }
    FILE* fp2 = fopen(dest_file, "w");
    if (fp2 == NULL) {
        printf("%s open failed.\n", dest_file);
        fclose(fp1);
        return;
    }
    int ch;
    while ((ch = fgetc(fp1)) != EOF) {
        fputc(ch, fp2);
    }
    fclose(fp1);
    fclose(fp2);
}

void copy_file_line(const char* src_file, const char* dest_file) {
    FILE* fp1 = fopen(src_file, "r");
    if (fp1 == NULL) {
        printf("%s open failed.\n", src_file);
        return;
    }
    FILE* fp2 = fopen(dest_file, "w");
    if (fp2 == NULL) {
        printf("%s open failed.\n", dest_file);
        fclose(fp1);
        return;
    }
    char buf[10] = { 0 };
    char* ret = NULL;
    while ((ret=fgets(buf,sizeof(buf),fp1) )!= NULL) {
        fputs(buf, fp2);
    }
    fclose(fp1);
    fclose(fp2);
}

void binary_file_cpy(const char* src_file, const char* dest_file) {
    FILE* fp1 = fopen(src_file, "rb");
    if (fp1 == NULL) {
        printf("%s open failed.\n", src_file);
        return;
    }
    FILE* fp2 = fopen(dest_file, "wb");
    if (fp2 == NULL) {
        printf("%s open failed.\n", dest_file);
        fclose(fp1);
        return;
    }
    char buf[10] = { 0 };
    int ret;
    while ((ret = fread(buf, 1, sizeof(buf), fp1)) >0) {
        fwrite(buf, 1, ret, fp2);
    }
    fclose(fp1);
    fclose(fp2);
}

typedef struct student {
    char name[20];
    int age;
    double score;
}Student;

void sequancify() {
    Student s1 = { "Marry",24,87.5 };
    FILE* fp = fopen("stu.dat", "wb");
    if (fp == NULL) {
        printf("open stu.dat failed.\n");
        return;
    }
    fwrite(&s1, sizeof(Student), 1, fp);
    fclose(fp);
    fp = fopen("stu.dat", "rb");
    if (fp == NULL) {
        printf("open stu.data failed.\n");
        return;
    }
    Student s2;
    fread(&s2, sizeof(Student), 1, fp);
    printf("姓名：%s，性别：%d，分数：%lf\n", s2.name, s2.age, s2.score);
    fclose(fp);
}

int main(void) {
    //copy_file_char("1.txt", "1_copy.txt");
    //copy_file_line("2.txt", "2_copy.txt");
    binary_file_cpy("3.png", "3.copy.png");
    //sequancify();
    return 0;
}
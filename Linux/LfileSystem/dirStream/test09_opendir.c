#include <my_header.h>

/*Usage:类比打开文件流 */
//int main(int argc,char *argv[])
//{
//    FILE*fp=fopen("1.txt","r");
//    ERROR_CHECK(fp,NULL,"fopen failed");
//    int ch;
//    while((ch=fgetc(fp))!=EOF){
//        printf("-----%c\n",ch);
//    }
//
//    fclose(fp);
//    return 0;
//}

//打开目录流
int main(int argc,char* argv[]){
    DIR*dirp=opendir("/home/vincio/repos/cpp-Microservices-Project/Linux/LfileSystem/dirStream");
    ERROR_CHECK(dirp,NULL,"opendir failed.");

    struct dirent*dirent_p=NULL;
    while((dirent_p=readdir(dirp))!=NULL){
    printf("%ld %s %ld\t %d %d\n",
           dirent_p->d_ino,dirent_p->d_name,dirent_p->d_off,
           dirent_p->d_reclen,dirent_p->d_type);
    }
//dirent.h中对文件类型进行了宏定义 REG普通文件 DIR目录
    printf("DT_REG=%d\n",DT_REG);
    printf("DT_DIR=%d\n",DT_DIR);

    closedir(dirp);
    return 0;
}

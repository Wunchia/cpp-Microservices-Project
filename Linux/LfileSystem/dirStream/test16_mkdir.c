#include <my_header.h>
#include <errno.h>

#define MAX_PATH 1024

/*Usage: */
int main(int argc,char *argv[])
{
    if(argc<2){
        printf("用法：%s <目标路径>\n",argv[0]);
        return -1;
    }

    char* base_path=argv[1];//存放需创建文件夹的路径
    char folder_path[MAX_PATH];//用于拼接第一层目录的路径
    char sub_folder_path[MAX_PATH];//用于拼接第二层目录的路径

    for(int i=1;i<=1000;i++){
        sprintf(folder_path,"%s/test%d",base_path,i);
        if(mkdir(folder_path,0777)!=0){
            if(errno!=EEXIST){
                perror("mkdir out failed.");
                continue;
            }
        }
        for(int j=1;j<=10;j++){
            int sub_num=i*10+j;
            sprintf(sub_folder_path,"%s/test%d",folder_path,sub_num);
            if(mkdir(sub_folder_path,0777)!=0){
                if(errno!=EEXIST){
                    perror("mkdir sub failed.");
                }
            }
        }

    }

    printf("mkdir finished.\n");
    return 0;
}


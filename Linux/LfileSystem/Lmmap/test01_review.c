#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    //参数检查，创建最外层目录，并进入
    ARGS_CHECK(argc,2);
    mkdir(argv[1],0777);
    chdir(argv[1]);
    //设置字符串准备拼接父目录名
    char father_path[100]={0};
    
    for(int i=1;i<=1000;i++){
        sprintf(father_path,"%s%d","test",i);//拼接字符串，生成父目录名
        mkdir(father_path,0777);//创建父目录
        chdir(father_path);//进入父目录
        char child_path[50]={0};//设置字符串准备拼接子目录名
        for(int j=1;j<=10;j++){
            sprintf(child_path,"%s%d","test",(i*10+j));//拼接字符串生成子目录名
            mkdir(child_path,0777);   //创建子目录
        }
        chdir("..");//返回上一层目录，准备创建下一个父目录
    }
    return 0;
}


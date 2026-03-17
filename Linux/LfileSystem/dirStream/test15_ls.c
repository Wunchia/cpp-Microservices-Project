#include <my_header.h>
#include <bits/types/stack_t.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>

void parse_file_type_and_mode(mode_t mode,char file_type_and_mode[]){
    char file_type='?';
    switch(mode & S_IFMT){
    case S_IFBLK:  file_type='b';   break;
    case S_IFCHR:  file_type='c';   break;
    case S_IFDIR:  file_type='d';   break;
    case S_IFIFO:  file_type='p';   break;
    case S_IFLNK:  file_type='l';   break;
    case S_IFREG:  file_type='-';   break;
    case S_IFSOCK: file_type='s';   break;
    default:       file_type='?';   break;
    }

    file_type_and_mode[0]=file_type;

    file_type_and_mode[1]=((mode&0400)!=0)?'r':'-';
    file_type_and_mode[2]=((mode&0200)!=0)?'w':'-';
    file_type_and_mode[3]=((mode&0100)!=0)?'x':'-';
    file_type_and_mode[4]=((mode&0040)!=0)?'r':'-';
    file_type_and_mode[5]=((mode&0020)!=0)?'w':'-';
    file_type_and_mode[6]=((mode&0010)!=0)?'x':'-';
    file_type_and_mode[7]=((mode&0004)!=0)?'r':'-';
    file_type_and_mode[8]=((mode&0002)!=0)?'w':'-';
    file_type_and_mode[9]=((mode&0001)!=0)?'x':'-';

    file_type_and_mode[10]='\0';
}

void parse_time_to_str(time_t sec,char *str){
    struct tm *tm_ret=localtime(&sec);
    tm_ret->tm_year+1900;
    tm_ret->tm_mon+1;
    tm_ret->tm_mday;
    sprintf(str, "%d-%02d-%02d %02d:%02d:%02d",
            tm_ret->tm_year + 1900,
            tm_ret->tm_mon + 1,
            tm_ret->tm_mday,
            tm_ret->tm_hour,
            tm_ret->tm_min,
            tm_ret->tm_sec);
}

/*Usage: */
int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    DIR*dirp=opendir(argv[1]);
    ERROR_CHECK(dirp,NULL,"opendir failed.");

    chdir(argv[1]);

    char path[100]={0};
    struct dirent *dirent_p=NULL;
    struct stat *stat_p=(struct stat*)calloc(1,sizeof(struct stat));
    ERROR_CHECK(stat_p,NULL,"calloc stat_p failed.");

    while((dirent_p=readdir(dirp))!=NULL){
        sprintf(path,"%s/%s",argv[1],dirent_p->d_name);

        int ret=stat(path,stat_p);
        ERROR_CHECK(ret,-1,"stat find path failed.");

        //转换
        char type_and_mode[20]={0};
        parse_file_type_and_mode(stat_p->st_mode,type_and_mode);

        char time_str[200]={0};
        parse_time_to_str(stat_p->st_mtime,time_str);

        printf("%s %ld %s %s %ld %s %s\n",
               type_and_mode,
               stat_p->st_nlink,
               getpwuid(stat_p->st_uid)->pw_name,
               getgrgid(stat_p->st_gid)->gr_name,
               stat_p->st_size,
               time_str,
               dirent_p->d_name
               );
    }

    closedir(dirp);

    return 0;
}


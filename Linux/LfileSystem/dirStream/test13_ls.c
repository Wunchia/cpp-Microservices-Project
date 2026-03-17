#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    DIR*dirp=opendir(argv[1]);
    ERROR_CHECK(dirp,NULL,"opendir failed.");

    chdir(argv[1]);

    struct dirent *dirent_p=NULL;
    struct stat *stat_p=(struct stat*)calloc(1,sizeof(struct stat));
    ERROR_CHECK(stat_p,NULL,"calloc stat_p failed.");

    while((dirent_p=readdir(dirp))!=NULL){
        int ret=stat(dirent_p->d_name,stat_p);
        ERROR_CHECK(ret,-1,"stat get name failed.");

        printf("%o %ld %d %d %ld %ld %s\n",
               stat_p->st_mode,
               stat_p->st_nlink,
               stat_p->st_uid,
               stat_p->st_gid,
               stat_p->st_size,
               stat_p->st_mtime,
               dirent_p->d_name
               );
    }

    closedir(dirp);

    return 0;
}


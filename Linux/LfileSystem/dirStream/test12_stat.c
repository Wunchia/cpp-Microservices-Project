#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    struct stat stat_buf;
    struct stat *stat_p=&stat_buf;
    
    int ret=stat("1.txt",stat_p);
    ERROR_CHECK(ret,-1,"stat failed.");
    printf("mode=%ld uid=%ld gid=%ld nlink=%ld size=%ld time=%ld\n",
           stat_p->st_mode,stat_p->st_uid,stat_p->st_gid,
           stat_p->st_nlink,stat_p->st_size,
           stat_p->st_mtim.tv_sec);

    return 0;
}


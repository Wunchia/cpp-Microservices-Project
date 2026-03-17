#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    struct stat stat_buf;
    stat("1.txt",&stat_buf);
    printf("blksize=%ld blocks=%ld dev=%ld gid=%ld ino=%ld\n mode=%d nlink=%d rdev=%d size=%d uid=%d\n",
           stat_buf.st_blksize,stat_buf.st_blocks,
           stat_buf.st_dev,stat_buf.st_gid,stat_buf.st_ino,
           stat_buf.st_mode,stat_buf.st_nlink,
           stat_buf.st_rdev,stat_buf.st_size,stat_buf.st_uid);
    return 0;
}


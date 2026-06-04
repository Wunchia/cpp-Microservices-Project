#include "common.h"
#include <fcntl.h>
#include <unistd.h>

int main(){
    int fd=open("a.txt",O_RDWR);
    assert(fd!=-1&&"open failed");

    char buf[4096]={0};
    //获取当前文件位置
    printf("pos: %ld\n",lseek(fd,0,SEEK_CUR));
    // write(fd,"kitty",5);
    pwrite(fd,"kitty",5,6);
    printf("pos: %ld\n",lseek(fd,0,SEEK_CUR));
    // printf("buf:%s\n",buf);
}

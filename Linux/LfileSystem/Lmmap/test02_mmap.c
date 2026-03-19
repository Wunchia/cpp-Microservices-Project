#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    int fd=open("1.txt",O_RDONLY);//以只读方式打开文件
    ERROR_CHECK(fd,-1,"open file failed.");
    
    //void *mmap(void *addr, size_t length, int prot, 
    //           int flags, int fd, off_t offset);
    //addr从哪里开始映射，建议写NULL
    //length、offset组合决定映射哪块进来
    //prot 映射进来后的权限 建议可读可写 PROT_READ|PROT_WRITE
    //flags 回写特点 建议MAP_SHARED
    //fd 打开的文件描述符
    char*p=(char*)mmap(NULL,10,PROT_READ,MAP_SHARED,fd,0);
    ERROR_CHECK(p,MAP_FAILED,"mmap to p failed.");

    for(int i=0;i<10;i++){
        printf("%d-----\n",p[i]);
    }

    munmap(p,10);
    close(fd);

    return 0;
}


#include <my_header.h>
#define ONCE_MAX_COPY_SIZE (1024*1024*16)
/*Usage: */
int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);
    int src_fd=open(argv[1],O_RDONLY);
    ERROR_CHECK(src_fd,-1,"open src failed.");
    int dest_fd=open(argv[2],O_RDWR|O_CREAT|O_TRUNC,0666);
    ERROR_CHECK(dest_fd,-1,"open dest failed.");
   
    //获取文件大小并预留空间
    struct stat stat_buf;
    fstat(src_fd,&stat_buf);

    long src_total_size=stat_buf.st_size;
    ftruncate(dest_fd,src_total_size);

    long copied_size=0;//记录已经拷贝的大小
    
    while(copied_size<src_total_size){
        //三目 确定当前这一次拷贝的大小 非最后一次都相同大小
        int cur_copy_size=(src_total_size-copied_size)>
            ONCE_MAX_COPY_SIZE?ONCE_MAX_COPY_SIZE:(src_total_size-copied_size);

        char*src_p=(char*)mmap(NULL,cur_copy_size,PROT_READ,
                               MAP_SHARED,src_fd,copied_size);
        ERROR_CHECK(src_p,MAP_FAILED,"mmap src failed.");

        char*dest_p=(char*)mmap(NULL,cur_copy_size,PROT_READ|PROT_WRITE,
                                MAP_SHARED,dest_fd,copied_size);
        ERROR_CHECK(dest_p,MAP_FAILED,"mmap dest failed.");
        //完成映射后直接memcpy
        memcpy(dest_p,src_p,cur_copy_size);
        munmap(src_p,cur_copy_size);
        munmap(dest_p,cur_copy_size);

        copied_size+=cur_copy_size;

    }

    close(src_fd);
    close(dest_fd);

    return 0;
}


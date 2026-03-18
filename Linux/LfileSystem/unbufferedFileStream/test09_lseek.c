#include <my_header.h>

long long current_time_millis(void) {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts); // 获取当前时间
    return (long long)ts.tv_sec * 1000LL + ts.tv_nsec / 1000000; // 转换为毫秒
}

/*Usage: */
int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);
    long long time1=current_time_millis();
    int src_fd=open(argv[1],O_RDONLY);
    ERROR_CHECK(src_fd,-1,"open src failed.");
    int dest_fd=open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0777);
    ERROR_CHECK(dest_fd,-1,"open dest failed.");

    off_t size_src=lseek(src_fd,0,SEEK_END);
    ERROR_CHECK(size_src,-1,"lseek failed.");
    lseek(src_fd,0,SEEK_SET);

    long long count=0;
    char* buf=(char*)malloc((long long)size_src+1);
    ERROR_CHECK(buf,NULL,"buf malloc failed.");
    while((count=read(src_fd,buf,size_src))!=0){
        write(dest_fd,buf,count);
    }
    close(src_fd);
    close(dest_fd);
    long long time2=current_time_millis();
    printf("time2-time1=%lld\n",(time2-time1));
    return 0;
}


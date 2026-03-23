#include <my_header.h>
#define CHUNK_SIZE (1024*1024)
/*Usage: */
int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);
    int fsrc=open(argv[1],O_RDONLY);
    ERROR_CHECK(fsrc,-1,"open src failed.");
    int fdst=open(argv[2],O_RDWR|O_CREAT|O_TRUNC,0666);
    
    struct stat st;
    fstat(fsrc,&st);
    off_t total_len=st.st_size;

    ftruncate(fdst,total_len);
    off_t offset=0;

    while(offset<total_len){
        size_t current_chunk=
            (total_len-offset>CHUNK_SIZE)?CHUNK_SIZE:(total_len-offset);

        void*src_addr=mmap(NULL,current_chunk,PROT_READ,MAP_SHARED,fsrc,offset);
        void*dst_addr=mmap(NULL,current_chunk,PROT_WRITE,MAP_SHARED,fdst,offset);
        if(src_addr==MAP_FAILED||dst_addr==MAP_FAILED){
            perror("mmap chunk failed");
            break;
        }
        memcpy(dst_addr,src_addr,current_chunk);
        munmap(src_addr,current_chunk);
        munmap(dst_addr,current_chunk);
        offset+=current_chunk;
    }

    close(fsrc);
    close(fdst);
    printf("Copy finished using mmap chunks.\n");
    return 0;
}


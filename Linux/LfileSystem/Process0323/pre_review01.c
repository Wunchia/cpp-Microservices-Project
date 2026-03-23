#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    int fd =open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"fd open failed.");
    struct stat st;
    fstat(fd,&st);
    size_t len =st.st_size;

    char *addr=(char *)mmap(NULL,len,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if(addr==MAP_FAILED){
        perror("mmap");
        return 1;
    }

    for(size_t i=0;i<len;i++){
        if(isupper(addr[i])){
            addr[i]=tolower(addr[i]);
        }
    }

    munmap(addr,len);
    close(fd);
    return 0;
}


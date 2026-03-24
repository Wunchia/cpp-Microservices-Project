#include <my_header.h>
#include <libgen.h>
#define FIFO_NAME "my_fifo"
#define BUFFER_SIZE 1024

typedef struct{
    char filename[256];
    long filesize;
}FileHeader;

void make_path(char*path){
    char temp[256];
    char*pos=NULL;
    strcpy(temp,path);
    for(pos=temp+1;*pos;pos++){
        if(*pos=='/'){
            *pos='\0';
            //F_OK 宏 检查文件是否存在 存在返回0 不存在返回-1
            if(access(temp,F_OK)!=0){
                mkdir(temp,0777);
            }
            *pos='/';
        }
    }
    if(access(temp,F_OK)!=0){
        mkdir(temp,0777);
    }
}
/*Usage: */
int main(int argc,char *argv[]){
    int fifo_fd,file_fd;
    FileHeader header;

    mkfifo(FIFO_NAME,0666);
    printf("waiting for usera sending ...\n");
    fifo_fd=open(FIFO_NAME,O_RDONLY);
    ERROR_CHECK(fifo_fd,-1,"pipe open failed.");

    if(read(fifo_fd,&header,sizeof(FileHeader))>0){
        printf("new task: creat file %s, size of file %ld Byte\n",header.filename,header.filesize);

        char path_copy[256];
        strcpy(path_copy,header.filename);
        char *dir=dirname(path_copy);
        make_path(dir);

        file_fd=open(header.filename,O_WRONLY|O_CREAT|O_TRUNC,0666);
        ERROR_CHECK(file_fd,-1,"create file failed.");
        char buffer[BUFFER_SIZE];
        ssize_t bytes_read;
        long total_received=0;

        while(total_received<header.filesize&&
              (bytes_read=read(fifo_fd,buffer,BUFFER_SIZE))>0){
            write(file_fd,buffer,bytes_read);
            total_received+=bytes_read;
        }
        printf("file received and restored successfully.\n");
        close(file_fd);
    }

    close(fifo_fd);
    unlink(FIFO_NAME);
    return 0;
}


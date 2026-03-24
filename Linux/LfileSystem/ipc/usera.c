#include <my_header.h>
#define FIFO_NAME "my_fifo"
#define BUFFER_SIZE 1024
/*Usage: */

typedef struct{
    char filename[256];
    long filesize;
}FileHeader;

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);
    int fifo_fd,file_fd;
    char *source_file=argv[1];
    char * target_path=argv[2];

    struct stat st;

    if(stat(source_file, &st)==-1){
        perror("can't get the info of src file.");
        return -1;
    }

    if(mkfifo(FIFO_NAME,0666)==-1){
        if(errno!=EEXIST){
            perror("mkfifo failed.");
            exit(EXIT_FAILURE);
        }
    }

    printf("waiting for userb to connect.\n");
    fifo_fd=open(FIFO_NAME,O_WRONLY);

    FileHeader header;
    strncpy(header.filename,target_path,256);
    header.filesize=st.st_size;
    write(fifo_fd,&header,sizeof(FileHeader));

    file_fd=open(source_file,O_RDONLY);
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    while((bytes_read=read(file_fd,buffer,BUFFER_SIZE))>0){
        write(fifo_fd,buffer,bytes_read);
    }
    printf("file send finished.\n");

    close(file_fd);
    close(fifo_fd);
    return 0;
}


#include <my_header.h>
#include "send_file.h"
void send_file(int fd){

    char *file_name="1.txt";

    int file_fd=open(file_name,O_RDWR);

    struct stat st;
    fstat(file_fd,&st);
    off_t file_len=st.st_size;//获得文件大小

    int len=strlen(file_name);//获得文件名大小

    //传一个int 文件名的长度
    send(fd,&len,sizeof(int),MSG_NOSIGNAL);

    //传文件名
    send(fd,file_name,len,MSG_NOSIGNAL);
    
    //传一个off_t 文件的长度
    send(fd,&file_len,sizeof(off_t),MSG_NOSIGNAL);

    //传文件 
    //sendfile(int out_fd,int in_fd,off_t offset,size_t count);
    sendfile(fd,file_fd,NULL,file_len);

    close(file_fd);
}
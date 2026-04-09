#include <my_header.h>
#include "send_file.h"

//如果客户端要求的文件不合法 则回传错误信息
void send_error_to_client(int fd,const char*err_msg){
    int error_flag=-1;
    send(fd,&error_flag,sizeof(int),MSG_NOSIGNAL);

    int msg_len=strlen(err_msg);
    send(fd,&msg_len,sizeof(int),MSG_NOSIGNAL);
    send(fd,err_msg,msg_len,MSG_NOSIGNAL);
}

void send_file(int fd){
    
    char file_name[60]={0};
    int get_len=0;

    int ret=recv(fd,&get_len,sizeof(int),MSG_WAITALL);
    ERROR_CHECK(ret,-1,"server recv len");
    //检查文件名长度是否合法
    if(get_len<=0||get_len>=sizeof(file_name)){
        printf("invalid file name length\n");
        send_error_to_client(fd,"invalid file_name length");
        return;
    }

    ret=recv(fd,file_name,get_len,MSG_WAITALL);
    ERROR_CHECK(ret,-1,"server recv name");
    //检查文件名是否合法
    if(0!=strcmp(file_name,"a.txt")&&0!=strcmp(file_name,"b.txt")){
        printf("no such file: %s\n",file_name);
        send_error_to_client(fd,"file not found");
        return;
    }

    //打开文件
    int file_fd=open(file_name,O_RDWR);
    ERROR_CHECK(file_fd,-1,"open file failed");

    //如果一切正常 顺利打开了文件 再走发送逻辑
    struct stat st;
    fstat(file_fd,&st);
    off_t file_len=st.st_size;

    int len=strlen(file_name);
    send(fd,&len,sizeof(int),MSG_NOSIGNAL);
    send(fd,file_name,len,MSG_NOSIGNAL);
    send(fd,&file_len,sizeof(off_t),MSG_NOSIGNAL);
    sendfile(fd,file_fd,NULL,file_len);

    close(file_fd);
}
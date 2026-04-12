#include <my_header.h>
#include "send_file.h"

void send_error_to_client(int fd,const char*err_msg){
    off_t error_flag=-1;
    //发送错误信号-1 客户端拿到-1后进入错误处理逻辑
    send(fd,&error_flag,sizeof(off_t),MSG_NOSIGNAL);

    //向客户端发送错误信息
    int msg_len=strlen(err_msg);
    send(fd,&msg_len,sizeof(int),MSG_NOSIGNAL);
    send(fd,err_msg,msg_len,MSG_NOSIGNAL);
}

void send_file(int fd){

    char file_name[60]={0};
    int name_len=0;
    //---------------处理客户端申请---------------
    int ret=recv(fd,&name_len,sizeof(int),MSG_WAITALL);
    ERROR_CHECK(ret,-1,"recv name_len");

    if(name_len<0||name_len>=sizeof(file_name)){
        printf("invalid file name length\n");
        send_error_to_client(fd,"invalid file name length");
        return;
    }

    ret=recv(fd,file_name,name_len,MSG_WAITALL);
    ERROR_CHECK(ret,-1,"recv file name");

    if(0!=strcmp(file_name,"a.txt")&&0!=strcmp(file_name,"b.txt")){
        printf("no such file:%s\n",file_name);
        send_error_to_client(fd,"no such file");
        return;
    }
    //--------------得到客户端申请的文件名-------------

    //打开文件
    int file_fd=open(file_name,O_RDWR);
    ERROR_CHECK(file_fd,-1,"open file failed");

    //开始发送逻辑
    struct stat st;
    fstat(file_fd,&st);
    off_t file_len=st.st_size;

    send(fd,&file_len,sizeof(off_t),MSG_NOSIGNAL);
    sendfile(fd,file_fd,NULL,file_len);

    close(file_fd);
    
}
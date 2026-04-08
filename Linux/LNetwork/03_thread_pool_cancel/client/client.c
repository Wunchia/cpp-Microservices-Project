#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    char *ip="192.168.171.128";
    char *port="12345";

    int client_fd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(client_fd,-1,"socket");

    struct sockaddr_in addr;
    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=inet_addr(ip);
    addr.sin_port=htons(atoi(port));

    int ret=connect(client_fd,(struct sockaddr*)&addr,sizeof(addr));
    ERROR_CHECK(ret,-1,"connect");

    int file_name_len=0;
    recv(client_fd,&file_name_len,sizeof(int),MSG_WAITALL);
    char file_name[60]={0};
    recv(client_fd,file_name,file_name_len,MSG_WAITALL);

    off_t file_size=0;
    recv(client_fd,&file_size,sizeof(off_t),MSG_WAITALL);
    printf("file_size:%ld\n",file_size);

    int file_fd=open(file_name,O_RDWR|O_CREAT,0600);
    ftruncate(file_fd,file_size);

    char*pmmap=(char*)mmap(NULL,file_size,PROT_READ|PROT_WRITE,MAP_SHARED,file_fd,0);
    recv(client_fd,pmmap,file_size,MSG_WAITALL);

    munmap(pmmap,file_size);
    close(file_fd);
    close(client_fd);
    return 0;
}


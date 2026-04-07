#include <my_header.h>
#include "send_file.h"
void send_file(int fd){
    int ret=send(fd,"hello",5,0);
    ERROR_CHECK(ret,-1,"send");
}
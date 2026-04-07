#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <my_header.h>

typedef struct node_s{
    int fd;
    struct node_s *pNext;
}node_t;

typedef struct queue_s{
    node_t *head;//队头指针
    node_t *rear;//队尾指针
    int size;//队列中元素个数
}queue_t;

//将文件描述符入队
int enQueue(queue_t *pQueue,int fd);

//将文件描述符出队
int deQueue(queue_t *pQueue,int *fd);

#endif
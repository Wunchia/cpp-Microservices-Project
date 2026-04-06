#ifndef __THREADQUEUE__
#define __THREADQUEUE__

#include <my_header.h>

typedef struct node_s{
    int net_fd;
    struct node_s *pNext;
}node_t;

typedef struct queue_s{
    node_t *head;
    node_t *end;
    int size;
}queue_t;

int enQueue(queue_t *pQueue,int net_fd);
int deQueue(queue_t *pQueue);

#endif
#include <my_header.h>
#include "queue.h"

int enQueue(queue_t *pQueue,int fd){
    node_t *pNew=(node_t*)calloc(1,sizeof(node_t));
    pNew->fd=fd;

    if(0==pQueue->size){
        pQueue->head=pNew;
        pQueue->rear=pNew;
    }else{
        pQueue->rear->pNext=pNew;
        pQueue->rear=pNew;
    }

    pQueue->size++;
    return 0;
}

int deQueue(queue_t *pQueue,int *fd){
    if(0==pQueue->size){
        return -1;
    }

    node_t *p=pQueue->head;
    pQueue->head=p->pNext;

    if(1==pQueue->size){
        pQueue->rear=NULL;
    }

    pQueue->size--;
    *fd=p->fd;
    free(p);

    return 0;
}
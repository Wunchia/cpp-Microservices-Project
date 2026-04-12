#include <my_header.h>
#include "queue.h"
int enQueue(queue_t*pQueue,int fd){
    node_t *pNew=(node_t*)calloc(1,sizeof(node_t));
    pNew->fd=fd;
    if(0==pQueue->size){
        pQueue->head=pNew;
        pQueue->rear=pNew;
        pNew->pNext=NULL;
        pQueue->size++;
        return 0;
    }
    pNew->pNext=pQueue->rear->pNext;
    pQueue->rear->pNext=pNew;
    pQueue->rear=pNew;
    pQueue->size++;
    return 0;
}

int deQueue(queue_t*pQueue,int *fd){
    if(0==pQueue->size){
        return -1;
    }

    node_t* pDel=pQueue->head;
    if(1==pQueue->size){
        *fd=pDel->fd;
        pQueue->head=NULL;
        pQueue->rear=NULL;
        pQueue->size--;
        free(pDel);
        return 0;
    }
    pQueue->head=pQueue->head->pNext;
    *fd=pDel->fd;
    pQueue->size--;
    free(pDel);
    return 0;
}
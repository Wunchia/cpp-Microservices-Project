#include "queue.h"

//将文件描述符入队
int enQueue(queue_t *pQueue,int fd){
    //新建节点
    node_t *pNew=(node_t *)calloc(1,sizeof(node_t));
    pNew->fd=fd;//存入fd

    if(0==pQueue->size){
        //队列为空
        pQueue->head=pNew;
        pQueue->rear=pNew;
    }else{
        //队列不空 插入队尾
        pQueue->rear->pNext=pNew;
        pQueue->rear=pNew;
    }

    pQueue->size++;
    
    return 0;
}

//将文件描述符出队
int deQueue(queue_t *pQueue,int *fd){
    if(0==pQueue->size){
        //队列为空 无法出队
        return -1;
    }

    //将队头元素出队
    node_t*p=pQueue->head;
    pQueue->head=p->pNext;

    *fd=p->fd;

    if(1==pQueue->size){
        //如果队中只剩最后一个元素 对尾指针置空
        pQueue->rear=NULL;
    }

    pQueue->size--;
    free(p);

    return 0;
}

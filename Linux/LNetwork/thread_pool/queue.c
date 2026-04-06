#include "queue.h"

/*Usage: */
int enQueue(queue_t *pQueue,int net_fd)
{
    node_t *pNew=(node_t *)calloc(1,sizeof(node_t));
    pNew->net_fd=net_fd;
    
    if(pQueue->size==0){

    }
    return 0;
}


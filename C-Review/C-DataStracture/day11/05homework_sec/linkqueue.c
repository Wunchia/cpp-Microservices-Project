#include "linkqueue.h"

// 创建链式队列
LinkedListQueue* create_queue() {
	LinkedListQueue* Lqueue = (LinkedListQueue*)malloc(sizeof(LinkedListQueue));
	if (Lqueue == NULL) {
		printf("malloc of Lqueue failed\n");
		return NULL;
	}
	Lqueue->front = NULL;
	Lqueue->rear = NULL;
	return Lqueue;
}

// 销毁链式队列
void destroy_queue(LinkedListQueue* q) {
	if (q == NULL) {
		return;
	}
	QueueNode* del = NULL;
	while (q->front != NULL) {
		del = q->front;
		q->front = q->front->next;
		free(del);
	}
	free(q);
}

// 入队列
bool enqueue(LinkedListQueue* q, ElementType element) {
	if (q == NULL) {
		return false;
	}
	QueueNode* new = (QueueNode*)malloc(sizeof(QueueNode));
	if (new == NULL) {
		return false;
	}
	new->data = element;
	new->next = NULL;
	if (NULL == q->rear) {
		q->front = new;
		q->rear = new;
		return true;
	}
	q->rear->next = new;
	q->rear = new;
	return true;
}

// 出队列并返回队头元素
ElementType dequeue(LinkedListQueue* q) {
	if (q == NULL || q->front == NULL) {
		printf("q is empty\n");
		return -1;
	}
	QueueNode* out = q->front;
	q->front = out->next;
	if (q->front == NULL) {
		q->rear = NULL;
	}
	ElementType ret = out->data;
	free(out);
	return ret;
}

// 访问队头元素
ElementType peek_queue(LinkedListQueue* q) {
	if (q == NULL || q->front == NULL) {
		printf("q is empty\n");
		return -1;
	}
	return q->front->data;
}

// 判空
bool is_empty(LinkedListQueue* q) {
	if (q == NULL||q->front==NULL) {
		return true;
	}
	return false;
}


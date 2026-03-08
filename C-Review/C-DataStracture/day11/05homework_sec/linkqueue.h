#ifndef LIST_QUEUE_H
#define LIST_QUEUE_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// 定义队列中的元素类型
typedef int ElementType;
// 队列节点的结构
typedef struct node_s {
	ElementType data;
	struct node_s* next;
} QueueNode;
// 队列的结构
typedef struct {
	QueueNode* front;  // 队头结点指针
	QueueNode* rear;   // 队尾结点指针
} LinkedListQueue;
// 创建链式队列
LinkedListQueue* create_queue();
// 销毁链式队列
void destroy_queue(LinkedListQueue* q);
// 入队列
bool enqueue(LinkedListQueue* q, ElementType element);
// 出队列并返回队头元素
ElementType dequeue(LinkedListQueue* q);
// 访问队头元素
ElementType peek_queue(LinkedListQueue* q);
// 判空
bool is_empty(LinkedListQueue* q);

#endif // !LIST_QUEUE_H

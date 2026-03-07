#ifndef LINKLIST_H
#define LINKLIST_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int DataType;

typedef struct node {
	DataType data;
	struct node* next;
}Node;

typedef struct linklist {
	Node* head;
	Node* rear;
	int size;
}Linklist;

// 创建一个空的链表
Linklist* create_linked_list();
// 销毁链表
void destroy_linked_list(Linklist* list);
// 头插法
bool add_before_head(Linklist* list, DataType new_data);
// 尾插法
bool add_behind_tail(Linklist* list, DataType new_data);
// 根据索引插入一个新结点
bool add_by_idx(Linklist* list, int idx, DataType new_data);
// 根据索引搜索一个结点
Node* search_by_idx(Linklist* list, int idx);
// 根据数据搜索一个结点
Node* search_by_data(Linklist* list, DataType data);
// 根据数据删除一个结点
bool delete_by_data(Linklist* list, DataType data);
// 扩展: 根据索引删除一个结点
bool delete_by_idx(Linklist* list, int idx);
// 打印单链表 格式为：1 -> 2 -> 3 ->...
void print_list(Linklist* list);

#endif
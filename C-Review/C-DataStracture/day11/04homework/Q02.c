#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
	int data;
	struct node* next;
} Node;

// 实现尾插法构建链表
void insert_tail(Node** head, int new_data) {
	// 1.分配新结点，初始化它
	Node* new_node = malloc(sizeof(Node));
	if (new_node == NULL) {
		printf("error: malloc failed in insert_tail.\n");
		exit(1);
	}
	new_node->data = new_data;
	new_node->next = NULL;
	// 3.链表非空时,让原本最后一个结点指向新结点
	if (*head != NULL) {
		// 2.遍历找到最后一个结点
		Node* end = *head;
		while (end->next != NULL) {
			end = end->next;
		} // while循环结束时, end指向最后一个结点
		end->next = new_node;
		return;
	}
	// 链表尾插之前是空的,那就直接更新头指针就行了
	*head = new_node;
}
//后续单链表的面试题，也请基于此链表结点的定义，以及尾插法构建链表实现。
//利用快慢指针法，直接求解下列两个问题：
//1.求链表中间结点的值
//2.判断单链表是否有环

int find_mid(Node* list) {
	Node* sp = list;
	Node* fp = list;
	while (fp != NULL && fp->next != NULL && fp->next->next != NULL) {
		fp = fp->next->next;
		sp = sp->next;
	}
	return sp->data;
}

bool is_loop(Node* list) {
	Node* sp = list;
	Node* fp = list;
	while (fp != NULL && fp->next != NULL && fp->next->next != NULL) {
		fp = fp->next->next;
		sp = sp->next;
		if (fp == sp) {
			return true;
		}
	}
	return false;
}

int main(void) {

	Node* head1 = NULL;
	for (int i = 0; i < 20; i++) {
		insert_tail(&head1, i);
	}
	printf("mid = %d\n", find_mid(head1));

	Node* head2 = NULL;
	for (int i = 0; i < 10; i++) {
		insert_tail(&head2, i);
	}
	Node* cur = head2;
	while (cur->next != NULL) {
		cur = cur->next;
	}
	cur->next = head2;
	if (is_loop(head2)) {
		printf("head2 is a loop\n");
	}
	return 0;
}
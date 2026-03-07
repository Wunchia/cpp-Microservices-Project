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

//给定一条单链表，请反转这条单链表。
//举例，
//输入 : 1 -- > 2 -- > 3
//输出: 3 -- > 2 -- > 1

//基于以下函数的声明实现：
//Node * reverse(Node * list); // 反转当前单链表并返回新的头指针
//注意：
//请采用循环迭代求解这个问题。递归可以看一下，可以选择不使用递归实现。
void print_list(Node*list) {
	Node* cur = list;
	while (cur != NULL) {
		printf("%d", cur->data);
		if (cur->next != NULL) {
			printf("-->");
		}
		cur = cur->next;
	}
	printf("\n");
}

Node* reverse(Node* list) {
	Node* pre = NULL;
	Node* cur = list;
	Node* next = NULL;
	while (cur != NULL) {
		next = cur->next;
		cur->next = pre;
		pre = cur;
		cur = next;
	}
	return pre;
}

int main(void) {
	Node* list = NULL;
	for (int i = 0; i < 4; i++) {
		insert_tail(&list, i);
	}
	print_list(list);
	Node* reversed_list=reverse(list);
	print_list(reversed_list);

	return 0;
}

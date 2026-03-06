//基于以下链表结点结构体类型的定义:
//在main函数中定义一个head头指针等于NULL代表此时单链表为空：
//Node* head = NULL;

//利用二级指针语法实现以下函数：

//注：尾插法会稍微麻烦一些，可以放在最后实现。

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct node {
	ElementType data;
	struct node* next;
} Node;

// 头插法新增一个结点
void insert_head(Node** head, ElementType new_val) {
	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->data = new_val;
	new_node->next = *head;
	*head = new_node;
}

// 修改第一个结点的元素值，如果链表为空，则用new_val初始化第一个结点
void modify_first_node(Node** head, ElementType new_val) {
	if (*head == NULL) {
		insert_head(head, new_val);
		return;
	}
	(*head)->data = new_val;
}

// 尾插法新增一个结点
void insert_tail(Node** head, ElementType new_val) {
	if ((*head) == NULL) {
		Node* new = (Node*)malloc(sizeof(Node));
		new->data = new_val;
		new->next = NULL;
		*head = new;
		return;
	}
	Node* cur = *head;
	while (cur->next != NULL) {
		cur = cur->next;
	}
	Node* new = (Node*)malloc(sizeof(Node));
	new->data = new_val;
	new->next = NULL;
	cur->next = new;
}

// 打印单链表 格式为：1 -> 2 -> 3 ->...
void print_list(Node* head) {
	if (head == NULL) {
		return;
	}
	Node* cur = head;
	while (cur!= NULL) {
		printf("%d", cur->data);
		if (cur->next != NULL) {
			printf("->");
		}
		cur = cur->next;
	}
	printf("\n");
}

int main(void) {
	Node* head = NULL;
	modify_first_node(&head, 3);
	print_list(head);
	insert_head(&head, 2);
	insert_head(&head, 2);
	print_list(head);
	modify_first_node(&head, 1);
	print_list(head);
	insert_tail(&head, 4);
	insert_tail(&head, 5);
	print_list(head);
	return 0;
}

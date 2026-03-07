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

//合并两条有序的单向链表，使得合并后的链表也是有序的(要求: 不能额外申请堆内存空间)。
//输入：
//list1 : 1 -- > 3 -- > 5
//list2: 2 -- > 4 -- > 6
//输出：
//1 -- > 2 -- > 3 -- > 4 -- > 5 -- > 6
//函数声明可以直接写:
//Node * merge_two_lists(Node * list1, Node * list2);
//请采用循环迭代求解这个问题。递归可以看一下，可以选择不使用递归实现。
//注：循环实现时，可以思考一下加头结点的实现与不加的区别。
//不仅要定义函数实现对应功能，还需要编写测试用例，进行测试。

Node* merge_two_lists(Node* list1, Node* list2) {
	Node* cur1 = list1;
	Node* cur2 = list2;
	Node dummy;
	dummy.next = NULL;
	Node* dum_cur = &dummy;
	while (cur1 != NULL && cur2 != NULL) {
		if (cur1->data <= cur2->data) {
			dum_cur->next = cur1;
			cur1 = cur1->next;
			dum_cur = dum_cur->next;
		}
		else {
			dum_cur->next = cur2;
			cur2 = cur2->next;
			dum_cur = dum_cur->next;
		}
	}
	while (cur1 != NULL) {
		dum_cur->next = cur1;
		dum_cur = dum_cur->next;
		cur1 = cur1->next;
	}
	while (cur2 != NULL) {
		dum_cur->next = cur2;
		dum_cur = dum_cur->next;
		cur2 = cur2->next;
	}
	return dummy.next;
}

void print_list(Node* list) {
	while (list) {
		printf("%d%s", list->data, list->next ? " --> " : "");
		list = list->next;
	}
	printf("\n");
}

int main(void) {
	Node* list1 = NULL;
	Node* list2 = NULL;
	for (int i = 1; i < 4; i++) {
		insert_tail(&list1, i * 2);
		insert_tail(&list2, i);
	}
	print_list(list1);
	print_list(list2);

	Node* new = merge_two_lists(list1, list2);
	print_list(new);

	return 0;
}
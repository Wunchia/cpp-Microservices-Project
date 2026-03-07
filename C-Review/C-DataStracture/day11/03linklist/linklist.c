#include "linklist.h"

// 创建一个空的链表
Linklist* create_linked_list() {
	Linklist* linklist = (Linklist*)malloc(sizeof(Linklist));
	if (linklist == NULL) {
		printf("malloc failed in create_linked_list\n");
		return NULL;
	}
	linklist->head = NULL;
	linklist->rear = NULL;
	linklist->size = 0;
	return linklist;
}

// 销毁链表
void destroy_linked_list(Linklist* list) {
	if (!list) {
		return;
	}
	Node* cur = list->head;
	while (cur != NULL) {
		Node* next = cur->next;
		free(cur);
		cur = next;
	}
	free(list);
}

// 头插法
bool add_before_head(Linklist* list, DataType new_data) {
	if (list->head == NULL) {
		Node* new = (Node*)malloc(sizeof(Node));
		if (new == NULL) {
			printf("malloc failed in add_before_head\n");
			return false;
		}
		new->data = new_data;
		new->next = NULL;
		list->head = new;
		list->rear = new;
		list->size++;
		return true;
	}
	Node* new = (Node*)malloc(sizeof(Node));
	if (new == NULL) {
		printf("malloc failed in add_before_head\n");
		return false;
	}
	new->data = new_data;
	new->next = list->head;
	list->head = new;
	list->size++;
	return true;
}

// 尾插法
bool add_behind_tail(Linklist* list, DataType new_data) {
	if (list->head == NULL) {
		Node* new = (Node*)malloc(sizeof(Node));
		if (new == NULL) {
			printf("malloc failed in add_behind_tail\n");
			return false;
		}
		new->data = new_data;
		new->next = NULL;
		list->head = new;
		list->rear = new;
		list->size++;
		return true;
	}
	Node* new = (Node*)malloc(sizeof(Node));
	if (new == NULL) {
		printf("malloc failed in add_behind_tail\n");
		return false;
	}
	new->data = new_data;
	new->next = NULL;
	list->rear->next = new;
	list->rear = new;
	list->size++;
	return true;
}

// 根据索引插入一个新结点
bool add_by_idx(Linklist* list, int idx, DataType new_data) {
	if (idx<0 || idx>list->size) {
		printf("illigal idx\n");
		return false;
	}
	if (idx == 0) {
		return add_before_head(list, new_data);

	}
	if (idx == list->size) {
		return add_behind_tail(list, new_data);
	}
	Node* cur = list->head;
	while ( idx> 1) {
		cur = cur->next;
		idx--;
	}
	Node* new = (Node*)malloc(sizeof(Node));
	if (new == NULL) {
		printf("malloc failed in add_by_idx\n");
		return false;
	}
	new->data = new_data;
	new->next = cur->next;
	cur->next = new;
	list->size++;
	return true;
}

// 根据索引搜索一个结点
Node* search_by_idx(Linklist* list, int idx) {
	if (idx < 0 || idx >= list->size) {
		printf("illegal idx\n");
		return NULL;
	}
	Node* cur = list->head;
	while (idx > 0) {
		cur = cur->next;
		idx--;
	}
	return cur;
}

// 根据数据搜索一个结点
Node* search_by_data(Linklist* list, DataType data) {
	if (list->head == NULL) {
		printf("list is empty\n");
		return NULL;
	}
	Node* cur = list->head;
	while (cur != NULL&&cur->data != data) {
		cur = cur->next;
	}
	if (cur == NULL) {
		printf("failed to find data\n");
	}
	return cur;
}

// 根据数据删除一个结点
bool delete_by_data(Linklist* list, DataType data) {
	if (list->head == NULL) {
		printf("list is empty\n");
		return false;
	}
	
	if (list->head->data == data) {
		if (list->head == list->rear) {
			free(list->head);
			list->head = NULL;
			list->rear = NULL;
			list->size--;
			return true;
		}
		else {
			Node* cur = list->head;
			list->head = list->head->next;
			free(cur);
			list->size--;
			return true;
		}
	}
	Node* cur = list->head;
	while (cur->next != NULL && cur->next->data != data) {
		cur = cur->next;
	}
	if (cur->next == NULL) {
		printf("failed to find\n");
		return false;
	}
	Node* del = cur->next;
	cur->next = del->next;
	if (del == list->rear) {
		list->rear = cur;
	}
	free(del);
	list->size--;
	return true;
}

// 扩展: 根据索引删除一个结点
bool delete_by_idx(Linklist* list, int idx) {
	if (list->head == NULL) {
		printf("list is empty\n");
		return false;
	}
	if (idx < 0 || idx >= list->size) {
		printf("illegal idx\n");
		return false;
	}
	if (idx == 0) {
		if (list->head == list->rear) {
			free(list->head);
			list->head = NULL;
			list->rear = NULL;
			list->size = 0;
			return true;
		}
		Node* cur = list->head;
		list->head = cur->next;
		free(cur);
		list->size--;
		return true;
	}
	if (idx == list->size - 1) {
		Node* cur = list->head;
		while (cur->next != list->rear) {
			cur = cur->next;
		}
		free(list->rear);
		list->rear = cur;
		cur->next = NULL;
		list->size--;
		return true;
	}
	Node* cur = list->head;
	while (idx > 1) {
		cur = cur->next;
		idx--;
	}
	Node* del = cur->next;
	cur->next = del->next;
	free(del);
	list->size--;
	return true;
}

// 打印单链表 格式为：1 -> 2 -> 3 ->...
void print_list(Linklist* list) {
	Node* cur = list->head;
	while (cur!=NULL) {
		printf("%d", cur->data);
		if (cur->next != NULL) {
			printf(" -> ");
		}
		cur = cur->next;
	}
	printf("\n");
}
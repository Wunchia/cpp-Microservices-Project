#include "linklist.h"

Node* reverse_linklist(Node* head) {
	if (head == NULL || head->next == NULL) {
		return head;
	}
	Node* cur = head;
	Node* prev = NULL;
	Node* next = NULL;
	while (cur != NULL) {
		next = cur->next;//存住下段
		cur->next = prev;//逆转指针
		prev = cur;//接住上段
		cur = next;//向后遍历
	}
	return prev;
}


Node* reverse_linklist_recursive(Node* head) {
	if (head == NULL || head->next == NULL) {
		return head;
	}
	Node* new_head = reverse_linklist_recursive(head->next);
	head->next->next = head;//将下一个节点的next指向自己
	head->next = NULL;//自己的next指向NULL
	return new_head;
}

int main(void) {
	LinkedList* list = create_linked_list();
	for (int i = 0; i < 10; i++) {
		add_behind_tail(list, i);
	}
	print_list(list);

	Node*new01=reverse_linklist(list->head);
	Node* temp = list->head;
	list->head = new01;
	list->tail = temp;
	print_list(list);
	

	Node*new02=reverse_linklist_recursive(list->head);
	temp = list->head;
	list->head = new02;
	list->tail = temp;
	print_list(list);

	destroy_linked_list(list);
	return 0;
}
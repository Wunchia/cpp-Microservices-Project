#include "linklist.h"

// 内部私有工具函数：创建一个新节点（不导出到头文件）
static Node* _create_node(DataType data) {
    Node* new_node=(Node*)malloc(sizeof(Node));
    if(new_node){
        new_node->data=data;
        new_node->next=NULL;
    }
    return new_node;
}

// 1. 创建一个空的链表
LinkedList* create_linked_list(){
    LinkedList*list=(LinkedList*)malloc(sizeof(LinkedList));
    if(list==NULL){
        return NULL;
    }
    list->head=NULL;
    list->tail=NULL;
    list->size=0;
    return list;
}

// 2. 销毁链表

void destroy_linked_list(LinkedList* list){
    if(list==NULL){
        return;
    }
    Node *cur=list->head;
    while(cur!=NULL){
        Node*temp=cur;
        cur=cur->next;
        free(temp);
    }
    free(list);
}

// 3. 头插法

bool add_before_head(LinkedList* list,DataType new_data){
    if(list==NULL){
        return false;
    }
    Node* new_node = _create_node(new_data);
    if (new_node == NULL) {
        return false;
    }
    if (list->size == 0) {
        list->head = list->tail = new_node;
    }
    else {
        new_node->next = list->head;
        list->head = new_node;
    }
    list->size++;
    return true;
}

// 4. 尾插法

bool add_behind_tail(LinkedList* list, DataType new_data) {
    if (list == NULL) {
        return false;
    }
    Node* new_node = _create_node(new_data);
    if (new_node == NULL) {
        return false;
    }
    if (list->size == 0) {
        list->head = list->tail = new_node;
    }
    else {
        list->tail->next = new_node;
        list->tail = new_node;
    }
    list->size++;
    return true;
}

// 5. 根据索引插入新结点

bool add_by_idx(LinkedList* list, int idx, DataType new_data) {
    if (list == NULL || idx<0 || idx>list->size) {
        return false;
    }
    if (idx == 0) {
        return add_before_head(list, new_data);
    }
    if (idx == list->size) {
        return add_behind_tail(list, new_data);
    }
    Node* prev = search_by_idx(list, idx - 1);
    Node* new_node = _create_node(new_data);
    if (new_node == NULL) {
        return false;
    }
    new_node->next = prev->next;
    prev->next = new_node;
    list->size++;
    return true;
}

// 6. 根据索引搜索结点

Node* search_by_idx(LinkedList* list, int idx) {
    if (list == NULL || idx<0 || idx>list->size) {
        return NULL;
    }
    if (idx == list->size - 1) {
        return list->tail;
    }
    Node* cur = list->head;
    for (int i = 0; i < idx; i++) {
        cur = cur->next;
    }
    return cur;
}

// 7. 根据数据搜索结点

Node* search_by_data(LinkedList* list, DataType data) {
    if (list == NULL) {
        return NULL;
    }
    Node* cur = list->head;
    while (cur != NULL) {
        if (cur->data == data) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

// 8. 根据索引删除结点 (先实现索引删除，逻辑更清晰)

bool delete_by_idx(LinkedList* list, int idx) {
    if (list == NULL || idx<0 || idx>list->size) {
        return NULL;
    }
    Node* to_delete = NULL;
    if (idx == 0) {
        to_delete = list->head;
        list->head = list->head->next;
        if (list->size == 1) {
            list->tail = NULL;
        }
    }
    else {
        Node* prev = search_by_idx(list, idx - 1);
        to_delete = prev->next;
        prev->next = to_delete->next;
        if (idx == list->size - 1) {
            list->tail = prev;
        }
    }
    free(to_delete);
    list->size--;
    return true;
}

// 9. 根据数据删除结点

bool delete_by_data(LinkedList* list, DataType data) {
    if (list == NULL || list->size == 0) {
        return false;
    }
    Node* cur = list->head;
    Node* prev = NULL;
    while (cur != NULL) {
        if (cur->data == data) {
            if (cur == list->head) {//被删为头节点
                list->head = cur->next;
                if (list->size == 1) {//被删为尾节点
                    list->tail = NULL;
                }
            }
            else {
                prev->next = cur->next;
                if (cur == list->tail) {//被删为尾节点
                    list->tail = prev;
                }
            }
            free(cur);
            list->size--;
            return true;
        }
        prev = cur;
        cur = cur->next;
    }
    return false;
}

// 10. 打印链表

void print_list(LinkedList* list) {
    if (list == NULL||list->size==0) {
        printf("list is empty\n");
        return;
    }
    Node* cur = list->head;
    while (cur) {
        printf("%d", cur->data);
        if (cur->next) {
            printf(" --> ");
        }
        cur = cur->next;
    }
    printf("\n");
}
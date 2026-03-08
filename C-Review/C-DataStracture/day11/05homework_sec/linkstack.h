#ifndef LINKED_STACK_H
#define LINKED_STACK_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
// 栈的一个结点栈帧,类型定义
typedef struct node_s {
	ElementType data;
	struct node_s* next;
}StackFrame;
typedef struct {
	StackFrame* top;	// 栈顶指针
}LinkedStack;

// 基本操作
// 创建链式栈
LinkedStack* stack_create();
// 销毁链式栈
void stack_destroy(LinkedStack* stack);
// 判空
bool is_empty(LinkedStack* stack);
// 入栈
void stack_push(LinkedStack* stack, ElementType data);
// 出栈并返回栈顶元素
ElementType stack_pop(LinkedStack* stack);
// 访问栈顶元素
ElementType stack_peek(LinkedStack* stack);

#endif // !LINKED_STACK_H
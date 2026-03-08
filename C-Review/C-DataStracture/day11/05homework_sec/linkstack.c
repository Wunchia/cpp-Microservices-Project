#include "linkstack.h"

LinkedStack* stack_create() {
	LinkedStack* Lstack = (LinkedStack*)malloc(sizeof(LinkedStack));
	if (Lstack == NULL) {
		return NULL;
	}
	Lstack->top = NULL;
	return Lstack;
}

void stack_destroy(LinkedStack* stack) {
	while (stack->top != NULL) {
		StackFrame* next = stack->top->next;
		free(stack->top);
		stack->top = next;
	}
	free(stack);
}

bool is_empty(LinkedStack* stack) {
	if (stack->top == NULL) {
		return true;
	}
	else {
		return false;
	}
}

void stack_push(LinkedStack*stack,ElementType data) {
	StackFrame* frame = (StackFrame*)malloc(sizeof(StackFrame));
	if (frame == NULL) {
		printf("malloc failed\n");
		return;
	}
	frame->data = data;
	frame->next = stack->top;
	stack->top = frame;
}

ElementType stack_pop(LinkedStack* stack) {
	if (is_empty(stack)) {
		printf("stack is empty\n");
		return -1;
	}
	ElementType ret = stack->top->data;
	StackFrame* del = stack->top;
	stack->top = stack->top->next;
	free(del);
	return ret;
}

ElementType stack_peek(LinkedStack* stack) {
	if (is_empty(stack)) {
		printf("stack is empty\n");
		return -1;
	}
	ElementType ret = stack->top->data;
	return ret;
}
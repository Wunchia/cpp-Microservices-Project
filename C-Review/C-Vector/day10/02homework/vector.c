#include "vector.h"

// 初始化一个Vector动态数组
Vector* vector_create(void) {
	Vector* temp = (Vector*)malloc(sizeof(Vector));
	if (temp == NULL) {
		printf("malloc of vector failed in vector_create.\n");
		return NULL;
	}
	temp->data = (ElementType*)malloc(VECTOR_INIT_CAPACITY*sizeof(ElementType));
	if (temp->data == NULL) {
		printf("malloc of vec_data failed in vector_create.\n");
		free(temp);
		return NULL;
	}
	temp->size = 0; 
	temp->capacity = VECTOR_INIT_CAPACITY;
	return temp;
}

// 销毁一个Vector动态数组，释放内存。
void vector_destroy(Vector** v) {
	free((*v)->data);
	(*v)->data = NULL;
	free(*v);
	*v = NULL;
}

// 向动态数组末尾添加一个元素
void vector_push_back(Vector* v, ElementType val) {
	if (v->size == v->capacity) {
		ElementType* temp = (ElementType*)realloc
		(v->data,(VECTOR_INIT_CAPACITY + VECTOR_EXTENT_CAPACITY) * sizeof(ElementType));
		if (temp == NULL) {
			printf("realloc of vector in vector_push_back failed.\n");
			return;
		}
		v->data = temp;
		v->capacity += VECTOR_EXTENT_CAPACITY;
	}
	v->data[v->size++] = val;
}

// 在动态数组最前面添加元素，所有元素依次后移
void vector_push_front(Vector* v, ElementType val) {
	if (v->size == v->capacity) {
		ElementType* temp = (ElementType*)realloc
		(v->data, (VECTOR_INIT_CAPACITY + VECTOR_EXTENT_CAPACITY) * sizeof(ElementType));
		if (temp == NULL) {
			printf("realloc of vector in vector_push_back failed.\n");
			return;
		}
		v->data = temp;
		v->capacity += VECTOR_EXTENT_CAPACITY;
	}
	for (int i = v->size; i > 0 ; i--) {
		v->data[i] = v->data[i - 1];
	}
	v->data[0] = val;
	v->size++;
}

// 将元素val添加到索引为idx的位置，idx后面的元素依次后移
void vector_insert(Vector* v, int idx, ElementType val) {
	if (v->size == v->capacity) {
		ElementType* temp = (ElementType*)realloc
		(v->data, (VECTOR_INIT_CAPACITY + VECTOR_EXTENT_CAPACITY) * sizeof(ElementType));
		if (temp == NULL) {
			printf("realloc of vector in vector_push_back failed.\n");
			return;
		}
		v->data = temp;
		v->capacity += VECTOR_EXTENT_CAPACITY;
	}
	for (int i = v->size; i > idx; i--) {
		v->data[i] = v->data[i - 1];
	}
	v->data[idx] = val;
	v->size++;
}

// 遍历打印整个Vector动态数组
void vector_print(Vector* v) {
	for (int i = 0; i < v->size; i++) {
		printf("%d ", v->data[i]);
	}
	printf("\n");
}
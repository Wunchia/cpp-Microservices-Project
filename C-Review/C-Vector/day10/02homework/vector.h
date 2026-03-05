#pragma once
#ifndef VECTOR_H
#define VECTOR_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define VECTOR_INIT_CAPACITY 10
#define VECTOR_EXTENT_CAPACITY 20

typedef int ElementType;

typedef struct {
    ElementType* data;   // 指向堆空间的数组
    int size;	// 元素的个数
    int capacity; // 数组的容量
} Vector;

// 初始化一个Vector动态数组
Vector* vector_create(void);

// 销毁一个Vector动态数组，释放内存。
void vector_destroy(Vector* v);

// 向动态数组末尾添加一个元素
void vector_push_back(Vector* v, ElementType val);

// 在动态数组最前面添加元素，所有元素依次后移
void vector_push_front(Vector* v, ElementType val);

// 将元素val添加到索引为idx的位置，idx后面的元素依次后移
void vector_insert(Vector* v, int idx, ElementType val);

// 遍历打印整个Vector动态数组
void vector_print(Vector* v);

#endif

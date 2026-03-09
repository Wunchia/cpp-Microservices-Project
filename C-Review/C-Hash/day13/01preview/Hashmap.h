#ifndef HASHMAP_H
#define HASHMAP_H
#define _CRT_SECURE_NOWARNINGS
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#define HASHMAP_INIT_CAPACITY 10
typedef char* KeyType;
typedef char* ValueType;

typedef struct node_s {
	KeyType key;
	ValueType value;
	struct node_s* next;
}KeyValueNode;

typedef struct {
	KeyValueNode* table[10];
	int length; // 数组的长度
	int size; // 键值对的个数。 
	uint32_t seed;
}HashMap;

// 函数声明。 
HashMap* hashmap_create();
void hashmap_destory(HashMap* map);
void hashmap_print(HashMap* map);

ValueType hashmap_put(HashMap* map, KeyType key, ValueType value);

ValueType hashmap_get(HashMap* map, KeyType key);
ValueType hashmap_remove(HashMap* map, KeyType key);

#endif // !HASHMAP_H


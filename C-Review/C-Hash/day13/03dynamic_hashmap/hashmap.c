#include "hashmap.h"

// 创建一个固定容量的哈希表
DynamicHashMap* hashmap_create() {
	DynamicHashMap* map = (DynamicHashMap*)calloc(1, sizeof(DynamicHashMap));
	map->buckets = (KeyValueNode**)calloc(HASHMAP_CAPACITY, sizeof(KeyValueNode));
	map->size = 0;
	map->capacity = HASHMAP_CAPACITY;
	map->hash_seed = time(NULL);
	return map;
}

// 销毁一个哈希表
void hashmap_destroy(DynamicHashMap* map) {
	if (map->size == 0) {
		free(map);
		return;
	}
	for (int i = 0; i < map->capacity; i++) {
		if (map->buckets[i]) {
			KeyValueNode* cur = map->buckets[i];
			while (cur != NULL) {
				KeyValueNode* temp = cur;
				cur = cur->next;
				free(temp);
			}
		}
	}
	free(map);
}

//=======================murmur_hash2============================
static uint32_t hash(const void* key, int len, uint32_t seed) {
	const uint32_t m = 0x5bd1e995;
	const int r = 24;
	uint32_t h = seed ^ len;
	const unsigned char* data = (const unsigned char*)key;

	while (len >= 4) {
		uint32_t k = *(uint32_t*)data;
		k *= m;
		k ^= k >> r;
		k *= m;
		h *= m;
		h ^= k;
		data += 4;
		len -= 4;
	}

	switch (len) {
	case 3: h ^= data[2] << 16;
	case 2: h ^= data[1] << 8;
	case 1: h ^= data[0];
		h *= m;
	};

	h ^= h >> 13;
	h *= m;
	h ^= h >> 15;

	return h;
}
//=======================murmur_hash2============================

// 插入一个键值对
ValueType hashmap_put(DynamicHashMap* map, KeyType key, ValueType val) {
	uint32_t hash_num = hash(key, strlen(key), map->hash_seed);
	uint32_t index = hash_num % map->capacity;
	KeyValueNode* cur = map->buckets[index];
	while (cur) {
		if (strcmp(cur->key, key) == 0) {
			ValueType old_value = cur->val;
			cur->val = val;
			return old_value;
		}
		cur = cur->next;
	}
	cur = (KeyValueNode*)malloc(sizeof(KeyValueNode));
	cur->key = key;
	cur->val = val;
	cur->next = map->buckets[index];
	map->buckets[index] = cur;
	map->size++;
	return NULL;
}

// 查询一个键值对
ValueType hashmap_get(DynamicHashMap* map, KeyType key) {
	uint32_t index = hash(key, strlen(key), map->hash_seed) % map->capacity;
	KeyValueNode* cur = map->buckets[index];
	while (cur) {
		if (strcmp(cur->key, key) == 0) {
			return cur->val;
		}
		cur = cur->next;
	}
	return NULL;
}

// 删除某个键值对
bool hashmap_remove(DynamicHashMap* map, KeyType key) {
	uint32_t index = hash(key, strlen(key), map->hash_seed) % map->capacity;
	KeyValueNode* cur = map->buckets[index];
	if (map->buckets[index] == NULL) {
		return false;
	}
	if (strcmp(cur->key, key) == 0) {
		map->buckets[index] = cur->next;
		free(cur);
		map->size--;
		return true;
	}
	KeyValueNode* prev = cur;
	cur = cur->next;
	while (cur) {
		if (strcmp(cur->key, key) == 0) {
			prev->next = cur->next;
			free(cur);
			map->size--;
			return true;
		}
		prev = cur;
		cur = cur->next;
	}
	return false;
}
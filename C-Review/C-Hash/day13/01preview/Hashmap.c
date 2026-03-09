#include "Hashmap.h"
/*

*/

HashMap* hashmap_create() {
    HashMap* map = (HashMap*)calloc(1,sizeof(HashMap));
    map->length = HASHMAP_INIT_CAPACITY;
    map->seed = time(NULL);
    return map;
}

void hashmap_destory(HashMap* map) {
    for (int i = 0; i < map->length; i++) {
        KeyValueNode* cur = map->table[i];

        while (cur != NULL) {
            KeyValueNode* temp = cur->next;
            free(cur);
            cur = temp;
        }
    }
    free(map);
}

void hashmap_print(HashMap* map) {
    for (int i = 0; i < map->length; i++) {
        KeyValueNode* cur = map->table[i];
        while (cur != NULL) {
            printf("key=%s,value=%s\n", cur->key, cur->value);
            cur = cur->next;
        }
    }
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

ValueType hashmap_put(HashMap* map, KeyType key, ValueType value) {
	uint32_t hash_num = hash(key, strlen(key), map->seed);
	int index = hash_num % map->length;
	KeyValueNode* cur = map->table[index];
	while (cur != NULL) {//¸Ä
		if(strcmp(cur->key,key)==0){
			ValueType old_value = cur->value;
			cur->value = value;
			return old_value;
		}
		cur = cur->next;
	}
	//Ôö
	KeyValueNode* new_node = (KeyValueNode*)malloc(sizeof(KeyValueNode));
	new_node->key = key;
	new_node->value = value;
	new_node->next = map->table[index];
	map->table[index] = new_node;
	map->size++;
}

ValueType hashmap_get(HashMap* map, KeyType key) {
	uint32_t hash_num = hash(key,strlen(key),map->seed);
	int index = hash_num % map->length;
	KeyValueNode* cur = map->table[index];
	while (cur != NULL) {
		if (strcmp(cur->key,key)==0) {
			return cur->value;
		}
		cur = cur->next;
	}
	return NULL;
}

ValueType hashmap_remove(HashMap* map, KeyType key) {
	int index = hash(key, strlen(key), map->seed) % map->length;
	KeyValueNode* cur = map->table[index];
	if (cur == NULL) {
		return NULL;
	}

	if (cur->key == key) {
		ValueType old_value = cur->value;
		map->table[index] = cur->next;
		free(cur);
		return old_value;
	}
	KeyValueNode* prev = cur;
	cur = cur->next;
	while (cur!=NULL) {
		if (strcmp(cur->key, key) == 0) {
			prev->next = cur->next;
			ValueType old_value = cur->value;
			free(cur);
			map->size--;
			return old_value;
		}
		prev = cur;
		cur = cur->next;
	}
	return NULL;
}

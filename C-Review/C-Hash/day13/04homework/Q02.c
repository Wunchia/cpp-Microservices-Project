#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
/*

*/
#define MAP_INIT_CAPACITY 1000

typedef struct hashnode {
    int key;
    int val;
    struct hashnode* next;
}HashNode;

typedef struct hashmap {
    HashNode* table[MAP_INIT_CAPACITY];
}HashMap;

bool insert(HashMap* map, int key, int val) {
    uint32_t index = abs(key) % MAP_INIT_CAPACITY;
    HashNode* cur = (HashNode*)malloc(sizeof(HashNode));
    if (cur == NULL) {
        return false;
    }
    cur->key = key;
    cur->val = val;
    cur->next=map->table[index];
    map->table[index] = cur;
    return true;
}

bool find(HashMap* map, int key,int*getidx) {
    uint32_t index = abs(key) % MAP_INIT_CAPACITY;
    HashNode* cur = map->table[index];
    while (cur != NULL) {
        if (cur->key == key) {
            *getidx = cur->val;
            return true;
        }
        cur = cur->next;
    }
    return false;
}

void destroy(HashMap* map) {
    if (map == NULL) return;

    // 1. 遍历哈希表数组的每一个索引
    for (int i = 0; i < MAP_INIT_CAPACITY; i++) {
        HashNode* cur = map->table[i];
        // 2. 遍历并释放该索引下的整个链表
        while (cur != NULL) {
            HashNode* temp = cur;
            cur = cur->next; // 先移动到下一个，防止丢失引用
            free(temp);      // 释放当前节点
        }
    }
    // 3. 最后释放哈希表结构体
    free(map);
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    HashMap* map = (HashMap*)calloc(1, sizeof(HashMap));
    for (int i = 0; i < numsSize; i++) {
        int ret = -1;
        if (find(map, target - nums[i], &ret)) {
            int *result = (int*)malloc(2 * sizeof(int));
            result[0] = i;
            result[1] = ret;
            *returnSize = 2;
            return result;
        }
        if (!insert(map, nums[i], i)) {
            return NULL;
        }
    }
    *returnSize = 0;
    destroy(map);
    return NULL;
}

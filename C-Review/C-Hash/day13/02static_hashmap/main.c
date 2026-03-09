#include "hashmap.h"

void hashmap_print(HashMap* map) {
	for (int i = 0; i < HASHMAP_CAPACITY;i++) {
		KeyValueNode* cur = map->buckets[i];
		while (cur != NULL) {
			printf("key=%s,val=%s\n", cur->key, cur->val);
			cur = cur->next;
		}
	}
}


int main(void) {
	HashMap* map = hashmap_create();
	char* old_value = NULL;
	hashmap_put(map, "110", "police\0");
	hashmap_put(map, "120", "ambulance\0");
	hashmap_put(map, "119", "fire department\0");
	hashmap_print(map);
	printf("110=>%s\n", hashmap_get(map, "110"));
	printf("119=>%s\n", hashmap_get(map, "119"));
	printf("120=>%s\n", hashmap_get(map, "120"));
	hashmap_remove(map, "110");
	hashmap_print(map);
	hashmap_destroy(map);
	return 0;
}
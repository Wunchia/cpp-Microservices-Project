#include "Hashmap.h"

int main(void) {
	HashMap* map = hashmap_create();
	char* old_value = NULL;
	hashmap_put(map, "110", "police\0");
	hashmap_put(map, "120", "ambulance\0");
	hashmap_put(map, "119", "fire department\0");
	hashmap_print(map);
	printf("110=>%s\n", hashmap_get(map,"110"));
	printf("119=>%s\n", hashmap_get(map,"119"));
	printf("120=>%s\n", hashmap_get(map,"120"));
	hashmap_remove(map, "110");
	hashmap_print(map);
	hashmap_destory(map);
	return 0;
}
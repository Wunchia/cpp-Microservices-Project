#include "vector.h"
int main(void) {

	Vector* v = vector_create();
	for (int i = 0; i < 10; i++) {
		vector_push_back(v, i);
	}
	vector_print(v);
	for (int i = 10; i < 15; i++) {
		vector_push_front(v, i);
	}
	vector_print(v);
	vector_insert(v, 5, 20);
	vector_print(v);

	vector_destroy(&v);

	if (v == NULL) {
		printf("v has been destroied.\n");
	}

	return 0;
}
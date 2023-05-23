#define DYN_ARRAY_IMPLEMENTATION
#include "dyn_array.h"

#include <stdio.h>

int main(void) {
	DArray* darray = darray_create(sizeof(int));
	int elem = 10;
	darray_push_back(darray, sizeof(int), &elem);

	for (size_t i = 0; i < darray->buf_size; i++) {
		int element = DARRAY_ELEMENT(darray, int, i);
		printf("%i, ", element);
	}
	printf("\n");

	return 0;
}
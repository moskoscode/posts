#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>


typedef struct Array {
	size_t capacity;
	size_t size;
	size_t item_size;
	void*  buffer;
} Array;


void _Array_realloc(Array* arr, size_t target_capacity) {
	if (arr->size > target_capacity)
		printf("ERROR: Can't target_capacity %zu cannot be less than Array.size %zu", target_capacity, arr->size);

	if (arr->buffer == NULL) {
		arr->buffer = malloc(target_capacity * arr->item_size);
		arr->capacity = target_capacity;

	} else {
		arr->buffer = realloc(arr->buffer, target_capacity * arr->item_size);
		arr->capacity = target_capacity;

	}

	if (arr->buffer == NULL) {
		printf("ERROR: Couldn't allocate enough memory");
		exit(-1);
	}
}

void Array_init(Array* arr, size_t item_size) {
	arr->capacity = 0;
	arr->size = 0;
	arr->item_size = item_size;
	arr->buffer = NULL;
}

void Array_add(Array* arr, const void* item) {
	if (arr->capacity == 0) {
		_Array_realloc(arr, 2);

	} else if (arr->size == arr->capacity) {
		_Array_realloc(arr, 2 * arr->size);

	}

	memcpy(((char*) arr->buffer) + (arr->size++ * arr->item_size), item, arr->item_size);
}

void* Array_get(Array* arr, size_t index) {
	if (index >= arr->size) return NULL;

	return ((char*) arr->buffer) + (index * arr->item_size);
}

void Array_remove(Array* arr, size_t index) {
	if (index >= arr->size) return;

	char* dest = ((char*) arr->buffer) + (index * arr->item_size);
	memcpy(dest, dest + arr->item_size, arr->size * arr->item_size - index * arr->item_size);
	arr->size--;
}

inline Array newArray(size_t item_size) {
	Array arr;
	Array_init(&arr, item_size);
	return arr;
}


int main() {
	Array ints = newArray(sizeof(int));
	printf("Array starts with %zu ints\n", ints.size);

	for (size_t i = 0; i < 15; ++i) {
		int temp = rand() % 100;
		Array_add(&ints, &temp);
	}

	Array_remove(&ints, 3);

	printf("Array now has %zu ints\n", ints.size);

	for (size_t i = 0; i < ints.size; ++i)
		printf("Index %zu is %i\n", i, *(int*) Array_get(&ints, i));


}


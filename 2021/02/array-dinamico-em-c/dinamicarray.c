#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>


// Dinamic Array struct
typedef struct Array {
	size_t capacidade;
	size_t tamanho;
	size_t item_tamanho;
	uint8_t*  buffer;
} Array;


void _Array_realloc(Array* arr, size_t target_capacidade) {
	if (arr->tamanho > target_capacidade)
		printf("ERROR: Can't target_capacidade %zu cannot be less than Array.tamanho %zu", target_capacidade, arr->tamanho);

	arr->buffer = realloc(arr->buffer, target_capacidade * arr->item_tamanho);
	arr->capacidade = target_capacidade;

	if (arr->buffer == NULL) {
		printf("ERROR: Couldn't allocate enough memory");
		exit(-1);
	}
}

void Array_init(Array* arr, size_t item_tamanho) {
	arr->capacidade = 0;
	arr->tamanho = 0;
	arr->item_tamanho = item_tamanho;
	arr->buffer = NULL;
}

void Array_deinit(Array* arr) {
	free(arr->buffer);
}

void Array_add(Array* arr, const void* item) {
	if (arr->capacidade == 0) {
		_Array_realloc(arr, 2);

	} else if (arr->tamanho == arr->capacidade) {
		_Array_realloc(arr, 2 * arr->tamanho);

	}

	memcpy(arr->buffer + arr->tamanho++ * arr->item_tamanho, item, arr->item_tamanho);
}

void* Array_get(Array* arr, size_t index) {
	if (index >= arr->tamanho) return NULL;

	return arr->buffer + index * arr->item_tamanho;
}

void Array_remove(Array* arr, size_t index) {
	if (index >= arr->tamanho) return;

	uint8_t* dest = arr->buffer + index * arr->item_tamanho;
	memcpy(dest, dest + arr->item_tamanho, arr->tamanho * arr->item_tamanho - index * arr->item_tamanho);
	arr->tamanho--;
}

int main() {
	Array ints;
	Array_init(&ints, sizeof(int));

	printf("Array starts with %zu ints\n", ints.tamanho);

	for (size_t i = 0; i < 15; ++i) {
		int temp = rand() % 100;
		Array_add(&ints, &temp);
	}

	Array_remove(&ints, 3);
	Array_remove(&ints, 10);
	Array_remove(&ints, 12);

	printf("Array now has %zu ints\n", ints.tamanho);

	for (size_t i = 0; i < ints.tamanho; ++i)
		printf("Index %zu is %i\n", i, *(int*) Array_get(&ints, i));

	Array_deinit(&ints);
}


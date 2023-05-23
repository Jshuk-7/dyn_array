#ifndef DYN_ARRAY_H
#define DYN_ARRAY_H

/*
MIT License

Copyright (c) 2023 Jshuk-7

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <stdint.h>
#include <string.h>

#ifndef DA_MALLOC
#include <stdlib.h>
#define DA_MALLOC malloc
#endif

#ifndef DA_REALLOC
#include <stdlib.h>
#define DA_REALLOC realloc
#endif

#ifndef DA_FREE
#include <stdlib.h>
#define DA_FREE free
#endif

#ifndef DA_ASSERT
#include <assert.h>
#define DA_ASSERT assert
#endif

#define DA_DEFAULT_CAPACITY 8

typedef struct
{
	uint8_t* buffer;
	size_t buf_size;
	size_t element_size;
	size_t capacity;
} DArray;

/// @brief Creates a new dynamic array.
/// @param element_size the size of each element in the array
/// @return new dynamic array
DArray* darray_create(size_t element_size);

/// @brief Reallocates the array's buffer to 'new_capacity'.
/// @param darray the array to modify
/// @param new_capacity the new capacity of the array
void darray_realloc(DArray* darray, size_t new_capacity);

/// @brief Pushes a new element to the array. This may involve a reallocation.
/// @param darray the array to modify
/// @param element_size the size of each element in the array
/// @param element a pointer to the element to push to the array
void darray_push_back(DArray* darray, size_t element_size, const void* element);

#define DARRAY_ELEMENT(darray, type, index) *((type*)(&(darray)->buffer[(darray)->element_size * (index)]))

#endif

#ifdef DYN_ARRAY_IMPLEMENTATION

DArray* darray_create(size_t element_size)
{
	DArray* darray = DA_MALLOC(sizeof(DArray));
	DA_ASSERT(darray != NULL);

	darray->element_size = element_size;
	darray->buf_size = 0;
	darray->capacity = DA_DEFAULT_CAPACITY;
	darray->buffer = DA_MALLOC(darray->capacity * darray->element_size);

	DA_ASSERT(darray->buffer != NULL);
	return darray;
}

void darray_realloc(DArray* darray, size_t new_capacity)
{
	DA_ASSERT(darray != NULL);
	DA_ASSERT(darray->buffer != NULL);
	darray->capacity = new_capacity;
	darray->buffer = DA_REALLOC(darray->buffer, darray->capacity * darray->element_size);
	DA_ASSERT(darray->buffer);
}

void darray_push_back(DArray* darray, size_t element_size, const void* element)
{
	DA_ASSERT(darray != NULL);
	DA_ASSERT(darray->buffer != NULL);
	DA_ASSERT(darray->element_size == element_size);

	if (darray->buf_size + 1 >= darray->capacity) {
		darray_realloc(darray, darray->capacity * 2);
	}

	memcpy(darray->buffer + (darray->buf_size * darray->element_size), element, element_size);
	darray->buf_size++;
}

#endif
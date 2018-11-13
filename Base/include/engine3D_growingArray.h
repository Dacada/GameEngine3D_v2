#ifndef GROWING_ARRAY_H
#define GROWING_ARRAY_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct engine3D_growingArray_t {
	size_t capacity; // capacity elements
	size_t elementSize; // of elementSize size
	size_t index; // last added element
	void *array; // pointer to first element
} engine3D_growingArray_t;

// Initialize array to a given capacity
void engine3D_growingArray_init(engine3D_growingArray_t *const array, const size_t elementSize, const size_t initialCapacity);

// Ensure array has enough capacity for calling add growth number of times
void engine3D_growingArray_ensureGrowth(engine3D_growingArray_t *const array, const size_t growth);

// Add element to array, grow capacity if necessary, element is uninitialized, return pointer to this element
void *engine3D_growingArray_add(engine3D_growingArray_t *const array);

// Finish array creation by optionally trimming with a final realloc to minimize memory consumption.
// With trim set to false this just returns array.array. With trim set to true you can't grow the array anymore.
void *engine3D_growingArray_finish(engine3D_growingArray_t *const array, bool trim);

// Return number of elements added to the growing array
size_t engine3D_growingArray_length(const engine3D_growingArray_t *const array);

// Get element of array at given index
void *engine3D_growingArray_getAt(const engine3D_growingArray_t *const array, size_t index);

// Completely discard the array, fees memory returned by growingArray_finish
void engine3D_growingArray_discard(engine3D_growingArray_t *const array);

#endif /* GROWING_ARRAY_H */

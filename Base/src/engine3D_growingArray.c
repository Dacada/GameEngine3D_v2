#include <engine3D_growingArray.h>
#include <engine3D_util.h>

#include <stdbool.h>

void engine3D_growingArray_init(engine3D_growingArray_t *const array, const size_t elementSize, const size_t initialCapacity) {
	array->capacity = initialCapacity;
	array->elementSize = elementSize;
	array->index = 0;
	array->array = engine3D_util_safeMalloc(elementSize * initialCapacity);
}

void engine3D_growingArray_ensureGrowth(engine3D_growingArray_t *const array, const size_t growth) {
	bool resize = false;
	while (array->index + growth > array->capacity) {
		array->capacity *= 2;
		resize = true;
	}
	if (resize) {
		array->array = engine3D_util_safeRealloc(array->array, array->capacity * array->elementSize);
	}
}

void *engine3D_growingArray_add(engine3D_growingArray_t *const array) {
	if (array->index + 1 > array->capacity) {
		array->capacity *= 2;
		array->array = engine3D_util_safeRealloc(array->array, array->capacity * array->elementSize);
	}
	return engine3D_growingArray_getAt(array, array->index++);
}

void *engine3D_growingArray_finish(engine3D_growingArray_t *const array, bool trim) {
	if (trim) {
		array->array = engine3D_util_safeRealloc(array->array, array->index * array->elementSize);
	}
	return array->array;
}

size_t engine3D_growingArray_length(const engine3D_growingArray_t *const array) {
	return array->index;
}

void *engine3D_growingArray_getAt(const engine3D_growingArray_t *const array, size_t index) {
  return (void*)((size_t)array->array + array->elementSize * index); // void pointer arithmetic is bad mkay
}

void engine3D_growingArray_discard(engine3D_growingArray_t *const array) {
	free(array->array);
	array->array = NULL;
}

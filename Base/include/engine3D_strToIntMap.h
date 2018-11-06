#ifndef ENGINE3D_STRTOINTMAP_H
#define ENGINE3D_STRTOINTMAP_H

#include "engine3D_growingArray.h"

#include <stdbool.h>
#include <stdlib.h>

#define ENGINE3D_STRTOINTMAP_HASHTABLE_ELEMENTS (512)
#define ENGINE3D_STRTOINTMAP_MAXKEYLEN (256)

typedef struct engine3D_strToIntMapBucket_t {
	char string[ENGINE3D_STRTOINTMAP_MAXKEYLEN];
	int integer;
} engine3D_strToIntMapBucket_t;

typedef struct engine3D_strToIntMap_t {
	engine3D_growingArray_t *buckets[ENGINE3D_STRTOINTMAP_HASHTABLE_ELEMENTS];
} engine3D_strToIntMap_t;

engine3D_strToIntMap_t *engine3D_strToIntMap_new(void);

void engine3D_strToIntMap_init(engine3D_strToIntMap_t *const map);

void engine3D_strToIntMap_add(engine3D_strToIntMap_t *const map, const char *const key, const int value);

int engine3D_strToIntMap_get(const engine3D_strToIntMap_t *const map, const char *const key);

#endif /* ENGINE3D_STRTOINTMAP_H */

#include <engine3D_strToIntMap.h>
#include <engine3D_util.h>

#include <string.h>

// http://www.cse.yorku.ca/~oz/hash.html
static size_t djb2_hash_str(const char *str) {
	size_t hash = 5381;
	int c;

	while ((c = *str++))
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash;
}

engine3D_strToIntMap_t *engine3D_strToIntMap_new(void) {
	return engine3D_util_safeMalloc(sizeof(engine3D_strToIntMap_t));
}

void engine3D_strToIntMap_init(engine3D_strToIntMap_t *const map) {
	for (size_t i = 0; i < ENGINE3D_STRTOINTMAP_HASHTABLE_ELEMENTS; i++) {
		map->buckets[i] = NULL;
	}
}

void engine3D_strToIntMap_destroy(const engine3D_strToIntMap_t *const map) {
	for (size_t i = 0; i < ENGINE3D_STRTOINTMAP_HASHTABLE_ELEMENTS; i++) {
		if (map->buckets[i] != NULL) {
			engine3D_growingArray_discard(map->buckets[i]);
		  free(map->buckets[i]);
		}
	}
}

void engine3D_strToIntMap_add(engine3D_strToIntMap_t *const map, const char *const key, const int value) {
	size_t hash = djb2_hash_str(key) % ENGINE3D_STRTOINTMAP_HASHTABLE_ELEMENTS;
	engine3D_growingArray_t *bucketsArray = map->buckets[hash];
	if (bucketsArray == NULL) {
		map->buckets[hash] = bucketsArray = engine3D_util_safeMalloc(sizeof(engine3D_growingArray_t));
		engine3D_growingArray_init(bucketsArray, sizeof(engine3D_strToIntMapBucket_t), 1);
	}
#ifdef DEBUG
	for (size_t i = 0; i < engine3D_growingArray_length(bucketsArray); i++) {
		engine3D_strToIntMapBucket_t bucket = ((engine3D_strToIntMapBucket_t*)bucketsArray->array)[i];
		if (strcmp(key, bucket.string) == 0) {
			engine3D_util_quit("attempt to add repeated key to strToIntMap");
		}
	}
#endif
	engine3D_strToIntMapBucket_t *currentBucket = engine3D_growingArray_add(bucketsArray);
	strncpy(currentBucket->string, key, ENGINE3D_STRTOINTMAP_MAXKEYLEN);
	currentBucket->integer = value;
}

int engine3D_strToIntMap_get(const engine3D_strToIntMap_t *const map, const char *const key) {
	size_t hash = djb2_hash_str(key) % ENGINE3D_STRTOINTMAP_HASHTABLE_ELEMENTS;
	engine3D_growingArray_t *bucketsArray = map->buckets[hash];
#ifdef DEBUG
	if (bucketsArray == NULL) {
		engine3D_util_quit("attempt to get non existant key from strToIntMap");
	}
#endif
	for (size_t i = 0; i < engine3D_growingArray_length(bucketsArray); i++) {
		engine3D_strToIntMapBucket_t bucket = ((engine3D_strToIntMapBucket_t*)bucketsArray->array)[i];
		if (strcmp(key, bucket.string) == 0) {
			return bucket.integer;
		}
	}
	engine3D_util_quit("attempt to get non existant key from strToIntMap");
}

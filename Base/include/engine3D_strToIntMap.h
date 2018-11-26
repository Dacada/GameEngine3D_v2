#ifndef ENGINE3D_STRTOINTMAP_H
#define ENGINE3D_STRTOINTMAP_H

#include "engine3D_growingArray.h"

#include <stdbool.h>
#include <stdlib.h>

#define ENGINE3D_STRTOINTMAP_HASHTABLE_ELEMENTS (512)
#define ENGINE3D_STRTOINTMAP_MAXKEYLEN (256)

// Hashtable bucket
typedef struct engine3D_strToIntMapBucket_t {
  char string[ENGINE3D_STRTOINTMAP_MAXKEYLEN]; // real string key, unhashed
  int integer; // value
} engine3D_strToIntMapBucket_t;

// A hashtable to map strings to integers
typedef struct engine3D_strToIntMap_t {
  engine3D_growingArray_t *buckets[ENGINE3D_STRTOINTMAP_HASHTABLE_ELEMENTS]; // A fixed array of pointers to buckets, which each contain the real unhashed key and the value
} engine3D_strToIntMap_t;

// Allocate and return a hashmap
engine3D_strToIntMap_t *engine3D_strToIntMap_new(void);

// Free a hashmap
void engine3D_strToIntMap_destroy(const engine3D_strToIntMap_t *const map);

// Initialize a hashmap after allocation
void engine3D_strToIntMap_init(engine3D_strToIntMap_t *const map);

// Add an element to the hashmap. If key was already added behaviour is undefined.
void engine3D_strToIntMap_add(engine3D_strToIntMap_t *const map, const char *const key, const int value);

// Get element in hashmap given the key
int engine3D_strToIntMap_get(const engine3D_strToIntMap_t *const map, const char *const key);

#endif /* ENGINE3D_STRTOINTMAP_H */

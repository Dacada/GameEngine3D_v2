#ifndef ENGINE3D_UTIL_H
#define ENGINE3D_UTIL_H

#include <GL/glew.h>
#include <stdlib.h>

#define UNUSED(x) (void)(x)

extern const char *engine3D_util_resourcesPath;

void engine3D_util_bail(const char *const message) __attribute__((noreturn));
void engine3D_util_quit(const char *const message) __attribute__((noreturn));

void engine3D_util_reportGlError(void);

int engine3D_util_errPrintf(const char *format, ...) __attribute__((format(printf, 1, 2)));
int engine3D_util_debugPrintf(const char *format, ...) __attribute__((format(printf, 1, 2)));

int engine3D_util_errPrint(const char *string);
int engine3D_util_debugPrint(const char *string);

void *engine3D_util_safeMalloc(const size_t size) __attribute__((malloc, alloc_size(1)));
void *engine3D_util_safeCalloc(const size_t nmemb, const size_t size) __attribute__((malloc, alloc_size(1, 2)));
void *engine3D_util_safeRealloc(void *ptr, const size_t size) __attribute__((alloc_size(2)));

#endif /* ENGINE3D_UTIL_H */

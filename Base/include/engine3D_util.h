#ifndef ENGINE3D_UTIL_H
#define ENGINE3D_UTIL_H

#include <GL/glew.h>
#include <stdlib.h>
#include <math.h>

// stop compiler from complaining about an unused variable
#define UNUSED(x) (void)(x)

// angle in degrees to radians
#define TO_RADIANS(angle) ((angle) / 180 * (float)M_PI)

// base path for the resources directory
extern const char *engine3D_util_resourcesPath;

// show an error message and abort
void engine3D_util_bail(const char *const message) __attribute__((noreturn));

// show an error message and exit
void engine3D_util_quit(const char *const message) __attribute__((noreturn));

// report any GL errors that might have happened
void engine3D_util_reportGlError(void);

// print an error message with printf format
int engine3D_util_errPrintf(const char *format, ...) __attribute__((format(printf, 1, 2)));

// print a message if in debug mode with printf format
int engine3D_util_debugPrintf(const char *format, ...) __attribute__((format(printf, 1, 2)));

// print an error message
int engine3D_util_errPrint(const char *string);

// print a message if in debug mode
int engine3D_util_debugPrint(const char *string);

// malloc, abort on error
void *engine3D_util_safeMalloc(const size_t size) __attribute__((malloc, alloc_size(1)));

// calloc, abort on error
void *engine3D_util_safeCalloc(const size_t nmemb, const size_t size) __attribute__((malloc, alloc_size(1, 2)));

// realloc, abort on error
void *engine3D_util_safeRealloc(void *ptr, const size_t size) __attribute__((alloc_size(2)));

#endif /* ENGINE3D_UTIL_H */

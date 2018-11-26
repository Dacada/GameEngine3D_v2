#ifndef ENGINE3D_TEXTURE_H
#define ENGINE3D_TEXTURE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

// texture for a 3D mesh
typedef struct engine3D_texture_t {
  GLuint id; // texture id
} engine3D_texture_t;

// take a pointer to a texture and load it from the given image file
engine3D_texture_t engine3D_texture_loadFromFile(const char *const filename);

// bind texture
void engine3D_texture_bind(engine3D_texture_t *const texture);

#endif /* ENGINE3D_TEXTURE_H */

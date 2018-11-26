#ifndef ENGINE3D_MESH_H
#define ENGINE3D_MESH_H

#include "engine3D_vertex.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <stdbool.h>

// 3D mesh
typedef struct engine3D_mesh_t {
  GLuint vbo; // vertex array vbo
  GLuint ibo; // index array ibo
  GLsizei len_vbo; //number of elements in the underlying vertex array vbo refers to
  GLsizei len_ibo; //number of elements in the underlying index array ibo refers to
} engine3D_mesh_t;

// Takes pointer to mesh struct, initializes it, returns same pointer
engine3D_mesh_t *engine3D_mesh_init(engine3D_mesh_t *const mesh);

// takes filename and pointer to mesh struct, creates vbo/ibo for vertices and indices from the .obj file
engine3D_mesh_t *engine3D_mesh_initFromFile(const char *const filename, engine3D_mesh_t *const mesh);

// Create vbo/ibo for the vertices/indices
engine3D_mesh_t *engine3D_mesh_addVertices(engine3D_mesh_t *const mesh, engine3D_vertex_t vertices[], size_t vertices_len, unsigned int indices[], const size_t indices_len, const bool doCalcNormals);

// render the mesh
void engine3D_mesh_draw(const engine3D_mesh_t *const mesh);

#endif /* ENGINE3D_MESH_H */

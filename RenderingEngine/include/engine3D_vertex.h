#ifndef ENGINE3D_VERTEX_H
#define ENGINE3D_VERTEX_H

#include <Base/engine3D_vector.h>

// vertex, vertices compose a mesh
typedef struct engine3D_vertex_t {
  engine3D_vector3f_t vec; //vertex
  engine3D_vector2f_t texCoord; //texture coordinate
  engine3D_vector3f_t normal; //normal
} engine3D_vertex_t;

// initialize a vertex as zero
void engine3D_vertex_initZero(engine3D_vertex_t *const vertex);

#endif /* ENGINE3D_VERTEX_H */

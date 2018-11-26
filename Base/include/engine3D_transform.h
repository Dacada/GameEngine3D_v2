#ifndef ENGINE3D_TRANSFORM_H
#define ENGINE3D_TRANSFORM_H

#include "engine3D_vector.h"

// Represents a transform for an object in a 3D space
typedef struct engine3D_transform_t {
  engine3D_vector3f_t pos; // position of the object in 3 axis
  engine3D_vector3f_t rot; // rotation of the object in 3 axis
  engine3D_vector3f_t scale; // scale of the object in 3 axis
} engine3D_transform_t;

// Set transform to default values: scale 1 and rotation and position 0
void engine3D_transform_reset(engine3D_transform_t *const transform);

// Get the transformation matrix from the transform
void engine3D_transform_getTransformation(const engine3D_transform_t *const transform, engine3D_matrix4f_t *const transformationMatrix);

#endif /* ENGINE3D_TRANSFORM_H */

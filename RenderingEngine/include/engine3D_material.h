#ifndef ENGINE3D_MATERIAL
#define ENGINE3D_MATERIAL

#include <Base/engine3D_vector.h>
#include "engine3D_texture.h"

// a material, including texture color and shader properties
typedef struct engine3D_material_t {
  engine3D_texture_t *texture; // texture
  engine3D_vector3f_t color; // color
  float specularIntensity; // for lighting
  float specularPower; // for lighting
} engine3D_material_t;

#endif /* ENGINE3D_MATERIAL */

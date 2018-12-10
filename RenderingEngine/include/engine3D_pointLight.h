#ifndef ENGINE3D_POINTLIGHT
#define ENGINE3D_POINTLIGHT

#include "engine3D_baseLight.h"
#include <Base/engine3D_vector.h>

typedef struct engine3D_attenuation_t {
  float constant;
  float linear;
  float exponent;
} engine3D_attenuation_t;

typedef struct engine3D_pointLight_t {
  engine3D_baseLight_t base;
  engine3D_attenuation_t atten;
  engine3D_vector3f_t position;
  float range;
} engine3D_pointLight_t;

#endif /* ENGINE3D_POINTLIGHT */

#ifndef ENGINE3D_POINTSPOT
#define ENGINE3D_POINTSPOT

#include "engine3D_baseLight.h"
#include "engine3D_pointLight.h"
#include <Base/engine3D_vector.h>

typedef struct engine3D_spotLight_t {
  engine3D_pointLight_t pointLight;
  engine3D_vector3f_t direction;
  float cutoff;
} engine3D_spotLight_t;

#endif /* ENGINE3D_SPOTLIGHT */

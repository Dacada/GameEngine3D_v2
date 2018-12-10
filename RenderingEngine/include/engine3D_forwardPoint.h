#ifndef ENGINE3D_FORWARDPOINT
#define ENGINE3D_FORWARDPOINT

#include "engine3D_shader.h"
#include "engine3D_material.h"
#include "engine3D_baseLight.h"
#include "engine3D_pointLight.h"

// a shader for point light
typedef struct engine3D_forwardPoint_t {
  engine3D_shader_t shader; // base shader fields
  engine3D_pointLight_t *pointLight;
} engine3D_forwardPoint_t;

// get instance of the shader
engine3D_forwardPoint_t *engine3D_forwardPoint_getInstance(void);

// destroy shader instance if it was created
void engine3D_forwardPoint_destroy(void);

#endif /* ENGINE3D_FORWARDPOINT */

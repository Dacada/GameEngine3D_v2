#ifndef ENGINE3D_FORWARDSPOT
#define ENGINE3D_FORWARDSPOT

#include "engine3D_shader.h"
#include "engine3D_material.h"
#include "engine3D_spotLight.h"

// a shader for spot light
typedef struct engine3D_forwardSpot_t {
  engine3D_shader_t shader; // base shader fields
  engine3D_spotLight_t *spotLight;
} engine3D_forwardSpot_t;

// get instance of the shader
engine3D_forwardSpot_t *engine3D_forwardSpot_getInstance(void);

// destroy shader instance if it was created
void engine3D_forwardSpot_destroy(void);

#endif /* ENGINE3D_FORWARDSPOT */

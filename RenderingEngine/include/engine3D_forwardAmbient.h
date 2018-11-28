#ifndef ENGINE3D_FORWARDAMBIENT
#define ENGINE3D_FORWARDAMBIENT

#include "engine3D_shader.h"
#include "engine3D_material.h"

// a shader for ambient light
typedef struct engine3D_forwardAmbient_t {
  engine3D_shader_t shader; // base shader fields
  engine3D_vector3f_t ambientIntensity;
} engine3D_forwardAmbient_t;

// get instance of the shader
engine3D_forwardAmbient_t *engine3D_forwardAmbient_getInstance(void);

// destroy shader instance if it was created
void engine3D_forwardAmbient_destroy(void);

#endif /* ENGINE3D_FORWARDAMBIENT */

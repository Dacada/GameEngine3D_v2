#ifndef ENGINE3D_FORWARDDIRECTIONAL
#define ENGINE3D_FORWARDDIRECTIONAL

#include "engine3D_shader.h"
#include "engine3D_material.h"
#include "engine3D_baseLight.h"
#include "engine3D_directionalLight.h"

// a shader for directional light
typedef struct engine3D_forwardDirectional_t {
  engine3D_shader_t shader; // base shader fields
  engine3D_directionalLight_t *directionalLight;
} engine3D_forwardDirectional_t;

// get instance of the shader
engine3D_forwardDirectional_t *engine3D_forwardDirectional_getInstance(void);

// destroy shader instance if it was created
void engine3D_forwardDirectional_destroy(void);

#endif /* ENGINE3D_FORWARDDIRECTIONAL */

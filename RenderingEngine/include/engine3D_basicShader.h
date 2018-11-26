#ifndef ENGINE3D_BASICSHADER
#define ENGINE3D_BASICSHADER

#include "engine3D_shader.h"
#include "engine3D_material.h"

// a basic shader
typedef struct engine3D_basicShader_t {
  engine3D_shader_t shader; // base shader fields
} engine3D_basicShader_t;

// get instance of the basic shader
engine3D_basicShader_t *engine3D_basicShader_getInstance(void);

// destroy a basic shader
void engine3D_basicShader_destroy(engine3D_basicShader_t *const shader);

#endif /* ENGINE3D_BASICSHADER */

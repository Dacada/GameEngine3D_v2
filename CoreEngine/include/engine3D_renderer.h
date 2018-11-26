#ifndef ENGINE3D_RENDERER_H
#define ENGINE3D_RENDERER_H

#include "engine3D_gameObject.h"

// renderer
typedef struct engine3D_renderer_t {
  int noEmptyStructPls;
} engine3D_renderer_t;

// initialize all rendering
engine3D_renderer_t *engine3D_renderer_init(engine3D_renderer_t *const renderer);

// render an object by rendering its components
void engine3D_renderer_render(const engine3D_renderer_t *const renderer, const engine3D_gameObject_t *const object);

// unbind all textures
void engine3D_renderer_unbindTextures(void);

// return a string representing the OpenGL version
const char *engine3D_renderer_getOpenGLVersion(void);

#endif /* ENGINE3D_RENDERER_H */

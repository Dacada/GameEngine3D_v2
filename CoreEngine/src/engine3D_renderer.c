#include <engine3D_renderer.h>
#include <RenderingEngine/engine3D_forwardAmbient.h>
#include <Base/engine3D_util.h>

static const engine3D_vector3f_t ambientLight = { 0.2f, 0.2f, 0.2f };

static void clearScreen(void) {
  // TODO: Stencil Buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

engine3D_renderer_t *engine3D_renderer_init(engine3D_renderer_t *const renderer) {
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  
  glFrontFace(GL_CW);
  glCullFace(GL_BACK);
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_DEPTH_CLAMP);
  glEnable(GL_TEXTURE_2D);
  
  return renderer;
}

void engine3D_renderer_render(const engine3D_renderer_t *const renderer, const engine3D_gameObject_t *const object) {
  UNUSED(renderer);
  clearScreen();

  engine3D_forwardAmbient_t *shader = engine3D_forwardAmbient_getInstance();
  shader->ambientIntensity = ambientLight;
  engine3D_gameObject_render(object, (engine3D_shader_t *)shader);
  
  //engine3D_gameObject_render(object, (engine3D_shader_t *)engine3D_basicShader_getInstance());
}

void engine3D_renderer_unbindTextures(void) {
  glBindTexture(GL_TEXTURE_2D, 0);
}

const char *engine3D_renderer_getOpenGLVersion(void) {
  return (char*)glGetString(GL_VERSION);
}

#include <engine3D_renderer.h>
#include <RenderingEngine/engine3D_forwardAmbient.h>
#include <RenderingEngine/engine3D_forwardDirectional.h>
#include <Base/engine3D_util.h>

static engine3D_vector3f_t ambientLight = { 0.1f, 0.1f, 0.1f };
static engine3D_directionalLight_t directionalLight1 = { { { 0.0f, 0.0f, 1.0f }, 0.4f }, { 1.0f, 1.0f, 1.0f } };
static engine3D_directionalLight_t directionalLight2 = { { { 1.0f, 0.0f, 0.0f }, 0.4f }, { -1.0f, 1.0f, -1.0f } };

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

  engine3D_forwardAmbient_t *ambientShader = engine3D_forwardAmbient_getInstance();
  ambientShader->ambientIntensity = ambientLight;
  engine3D_gameObject_render(object, (engine3D_shader_t *)ambientShader);
  
  glEnable(GL_BLEND);
  glBlendFunc(GL_ONE, GL_ONE);
  glDepthMask(false);
  glDepthFunc(GL_EQUAL);

  engine3D_forwardDirectional_t *directionalShader = engine3D_forwardDirectional_getInstance();
  directionalShader->directionalLight = &directionalLight1;
  engine3D_gameObject_render(object, (engine3D_shader_t *)directionalShader);
  directionalShader->directionalLight = &directionalLight2;
  engine3D_gameObject_render(object, (engine3D_shader_t *)directionalShader);

  glDepthFunc(GL_LESS);
  glDepthMask(true);
  glDisable(GL_BLEND);
  
  //engine3D_gameObject_render(object, (engine3D_shader_t *)engine3D_basicShader_getInstance());
}

void engine3D_renderer_unbindTextures(void) {
  glBindTexture(GL_TEXTURE_2D, 0);
}

const char *engine3D_renderer_getOpenGLVersion(void) {
  return (char*)glGetString(GL_VERSION);
}

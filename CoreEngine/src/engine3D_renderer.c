#include <engine3D_renderer.h>
#include <RenderingEngine/engine3D_forwardAmbient.h>
#include <RenderingEngine/engine3D_forwardDirectional.h>
#include <RenderingEngine/engine3D_forwardPoint.h>
#include <RenderingEngine/engine3D_forwardSpot.h>
#include <Base/engine3D_util.h>

static engine3D_vector3f_t ambientLight = { 0.1f, 0.1f, 0.1f };
//static engine3D_directionalLight_t directionalLight1 = { { { 0.0f, 0.0f, 1.0f }, 0.4f }, { 1.0f, 1.0f, 1.0f } };
//static engine3D_directionalLight_t directionalLight2 = { { { 1.0f, 0.0f, 0.0f }, 0.4f }, { -1.0f, 1.0f, -1.0f } };
//#define POINTLIGHTSLENX 4
//#define POINTLIGHTSLENY 4
//static engine3D_pointLight_t pointLights[POINTLIGHTSLENX * POINTLIGHTSLENY];
//#define POINTLIGHTSLEN2X 3
//#define POINTLIGHTSLEN2Y 3
//static engine3D_pointLight_t pointLights2[POINTLIGHTSLEN2X * POINTLIGHTSLEN2Y];
static engine3D_spotLight_t spotLight = {
  .pointLight = {
    .base={
      .color={0,1,0},
      .intensity=0.9f
    },
    .atten={
      .constant=0,
      .linear=0,
      .exponent=0.1f
    },
    .position={10,0.4f,10},
    .range=100
  },
  .direction = {1,0,0},
  .cutoff = 0
};

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
  /*
  for (int i=0; i<POINTLIGHTSLENX; i++) {
    for (int j=0; j<POINTLIGHTSLENY; j++) {
      pointLights[i+j*POINTLIGHTSLENY].base.color.x = 0;
      pointLights[i+j*POINTLIGHTSLENY].base.color.y = 0.5;
      pointLights[i+j*POINTLIGHTSLENY].base.color.z = 1;
      pointLights[i+j*POINTLIGHTSLENY].base.intensity = 0.4f;
      pointLights[i+j*POINTLIGHTSLENY].atten.constant = 0;
      pointLights[i+j*POINTLIGHTSLENY].atten.linear = 0;
      pointLights[i+j*POINTLIGHTSLENY].atten.exponent = 1;
      pointLights[i+j*POINTLIGHTSLENY].position.x = 11.5f*i - 7;
      pointLights[i+j*POINTLIGHTSLENY].position.y = 0.4f;
      pointLights[i+j*POINTLIGHTSLENY].position.z = 11.5f*j - 7; 
      pointLights[i+j*POINTLIGHTSLENY].range = 100;
    }
  }
  
  for (int i=0; i<POINTLIGHTSLEN2X; i++) {
    for (int j=0; j<POINTLIGHTSLEN2Y; j++) {
      if (i == j && i == 1) continue;
      pointLights2[i+j*POINTLIGHTSLEN2Y].base.color.x = 1;
      pointLights2[i+j*POINTLIGHTSLEN2Y].base.color.y = 0.5;
      pointLights2[i+j*POINTLIGHTSLEN2Y].base.color.z = 0;
      pointLights2[i+j*POINTLIGHTSLEN2Y].base.intensity = 0.4f;
      pointLights2[i+j*POINTLIGHTSLEN2Y].atten.constant = 0;
      pointLights2[i+j*POINTLIGHTSLEN2Y].atten.linear = 0;
      pointLights2[i+j*POINTLIGHTSLEN2Y].atten.exponent = 1;
      pointLights2[i+j*POINTLIGHTSLEN2Y].position.x = 11.5f*i - 1.25;
      pointLights2[i+j*POINTLIGHTSLEN2Y].position.y = 0.4f;
      pointLights2[i+j*POINTLIGHTSLEN2Y].position.z = 11.5f*j - 1.25;
      pointLights2[i+j*POINTLIGHTSLEN2Y].range = 100;
    }
  }
  
  pointLights2[1+POINTLIGHTSLEN2Y].base.color.x = 0.25;
  pointLights2[1+POINTLIGHTSLEN2Y].base.color.y = 1;
  pointLights2[1+POINTLIGHTSLEN2Y].base.color.z = 0.25;
  pointLights2[1+POINTLIGHTSLEN2Y].base.intensity = 0.4f;
  pointLights2[1+POINTLIGHTSLEN2Y].atten.constant = 0;
  pointLights2[1+POINTLIGHTSLEN2Y].atten.linear = 0;
  pointLights2[1+POINTLIGHTSLEN2Y].atten.exponent = 1;
  pointLights2[1+POINTLIGHTSLEN2Y].position.x = 11.5f - 1.25;
  pointLights2[1+POINTLIGHTSLEN2Y].position.y = 0.4f;
  pointLights2[1+POINTLIGHTSLEN2Y].position.z = 11.5f - 1.25;
  pointLights2[1+POINTLIGHTSLEN2Y].range = 100;
  */
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

  /*
  engine3D_forwardDirectional_t *directionalShader = engine3D_forwardDirectional_getInstance();
  directionalShader->directionalLight = &directionalLight1;
  engine3D_gameObject_render(object, (engine3D_shader_t *)directionalShader);
  directionalShader->directionalLight = &directionalLight2;
  engine3D_gameObject_render(object, (engine3D_shader_t *)directionalShader);
  

  engine3D_forwardPoint_t *pointShader = engine3D_forwardPoint_getInstance();
  for (int i=0; i<POINTLIGHTSLENX * POINTLIGHTSLENY; i++) {
    pointShader->pointLight = pointLights + i;
    engine3D_gameObject_render(object, (engine3D_shader_t*)pointShader);
  }
  for (int i=0; i<POINTLIGHTSLEN2X * POINTLIGHTSLEN2Y; i++) {
    pointShader->pointLight = pointLights2 + i;
    engine3D_gameObject_render(object, (engine3D_shader_t*)pointShader);
  }
  */

  engine3D_forwardSpot_t *spotShader = engine3D_forwardSpot_getInstance();
  spotShader->spotLight = &spotLight;
  engine3D_gameObject_render(object, (engine3D_shader_t*)spotShader);

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

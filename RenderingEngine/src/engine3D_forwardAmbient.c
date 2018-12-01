#include <engine3D_forwardAmbient.h>
#include <engine3D_shader.h>
#include <Base/engine3D_util.h>

static engine3D_forwardAmbient_t instance;
static bool isLoaded = false;

static void updateUniforms(engine3D_shader_t * const s, const engine3D_transform_t *const transform, const engine3D_camera_t *const camera, const engine3D_material_t *const material) {
  engine3D_forwardAmbient_t *shader = (engine3D_forwardAmbient_t*)s;

  engine3D_matrix4f_t worldMatrix, viewProjection, projectedMatrix;
  engine3D_transform_getTransformation(transform, &worldMatrix);
  engine3D_camera_getViewProjection(camera, &viewProjection);
  engine3D_matrix4f_mul(&viewProjection, &worldMatrix, &projectedMatrix);

  engine3D_texture_bind(material->texture);
  
  engine3D_shader_setUniformMat4f("MVP", &projectedMatrix, (engine3D_shader_t*)shader);
  engine3D_shader_setUniformVec3f("ambientIntensity", shader->ambientIntensity, (engine3D_shader_t*)shader);
}

engine3D_forwardAmbient_t *engine3D_forwardAmbient_getInstance(void) {
  if (!isLoaded) {
    engine3D_shader_init((engine3D_shader_t*)&instance);
    instance.shader.updateUniforms = &updateUniforms;
    
    engine3D_shader_addVertexShaderFromFile("forward-ambient.vs", (engine3D_shader_t*)&instance);
    engine3D_shader_addFragmentShaderFromFile("forward-ambient.fs", (engine3D_shader_t*)&instance);
    engine3D_shader_compile((engine3D_shader_t*)&instance);
    
    engine3D_shader_addUniform("MVP", (engine3D_shader_t*)&instance);
    engine3D_shader_addUniform("ambientIntensity", (engine3D_shader_t*)&instance);
    
    isLoaded = true;
  }
  
  return &instance;
}

void engine3D_forwardAmbient_destroy(void) {
  if (isLoaded)
    engine3D_shader_destroy((engine3D_shader_t*)&instance);
}

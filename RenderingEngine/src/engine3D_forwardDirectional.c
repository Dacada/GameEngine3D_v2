#include <engine3D_forwardDirectional.h>
#include <engine3D_shader.h>
#include <Base/engine3D_util.h>

static engine3D_forwardDirectional_t instance;
static bool isLoaded = false;

static void updateUniforms(engine3D_shader_t * const s, const engine3D_transform_t *const transform, const engine3D_camera_t *const camera, const engine3D_material_t *const material) {
  engine3D_forwardDirectional_t *shader = (engine3D_forwardDirectional_t*)s;

  engine3D_matrix4f_t worldMatrix, viewProjection, projectedMatrix;
  engine3D_transform_getTransformation(transform, &worldMatrix);
  engine3D_camera_getViewProjection(camera, &viewProjection);
  engine3D_matrix4f_mul(&viewProjection, &worldMatrix, &projectedMatrix);

  engine3D_texture_bind(material->texture);
  
  engine3D_shader_setUniformMat4f("model", &worldMatrix, s);
  engine3D_shader_setUniformMat4f("MVP", &projectedMatrix, s);
  
  engine3D_shader_setUniformf("specularIntensity", material->specularIntensity, s);
  engine3D_shader_setUniformf("specularPower", material->specularPower, s);
  
  engine3D_shader_setUniformVec3f("eyePos", camera->pos, s);
  
  engine3D_shader_setUniformDirectionalLight("directionalLight", shader->directionalLight, s);
}

engine3D_forwardDirectional_t *engine3D_forwardDirectional_getInstance(void) {
  if (!isLoaded) {
    engine3D_shader_init((engine3D_shader_t*)&instance);
    instance.shader.updateUniforms = &updateUniforms;
    
    engine3D_shader_addVertexShaderFromFile("forward-directional.vs", (engine3D_shader_t*)&instance);
    engine3D_shader_addFragmentShaderFromFile("forward-directional.fs", (engine3D_shader_t*)&instance);
    engine3D_shader_compile((engine3D_shader_t*)&instance);
    
    engine3D_shader_addUniform("model", (engine3D_shader_t*)&instance);
    engine3D_shader_addUniform("MVP", (engine3D_shader_t*)&instance);
    
    engine3D_shader_addUniform("specularIntensity", (engine3D_shader_t*)&instance);
    engine3D_shader_addUniform("specularPower", (engine3D_shader_t*)&instance);
    
    engine3D_shader_addUniform("eyePos", (engine3D_shader_t*)&instance);
    
    engine3D_shader_addUniform("directionalLight.base.color", (engine3D_shader_t*)&instance);
    engine3D_shader_addUniform("directionalLight.base.intensity", (engine3D_shader_t*)&instance);
    engine3D_shader_addUniform("directionalLight.direction", (engine3D_shader_t*)&instance);
    
    isLoaded = true;
  }
  
  return &instance;
}

void engine3D_forwardDirectional_destroy(void) {
  if (isLoaded)
    engine3D_shader_destroy((engine3D_shader_t*)&instance);
}

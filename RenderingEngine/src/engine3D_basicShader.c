#include <engine3D_basicShader.h>
#include <engine3D_shader.h>
#include <Base/engine3D_util.h>

static engine3D_basicShader_t instance;
static bool isLoaded = false;

void updateUniforms(engine3D_shader_t * const s, const engine3D_transform_t *const transform, const engine3D_camera_t *const camera, const engine3D_material_t *const material) {
  engine3D_basicShader_t *shader = (engine3D_basicShader_t*)s;

  engine3D_matrix4f_t worldMatrix, viewProjection, projectedMatrix;
  engine3D_transform_getTransformation(transform, &worldMatrix);
  engine3D_camera_getViewProjection(camera, &viewProjection);
  engine3D_matrix4f_mul(&viewProjection, &worldMatrix, &projectedMatrix);

  engine3D_texture_bind(material->texture);
  
  engine3D_shader_setUniformMat4f("transform", &projectedMatrix, (engine3D_shader_t*)shader);
  engine3D_shader_setUniformVec3f("color", material->color, (engine3D_shader_t*)shader);
}

engine3D_basicShader_t *engine3D_basicShader_getInstance(void) {
  if (!isLoaded) {
    engine3D_shader_init((engine3D_shader_t*)&instance);
    instance.shader.updateUniforms = &updateUniforms;
    
    engine3D_shader_addVertexShaderFromFile("basicVertex.vs", (engine3D_shader_t*)&instance);
    engine3D_shader_addFragmentShaderFromFile("basicFragment.fs", (engine3D_shader_t*)&instance);
    engine3D_shader_compile((engine3D_shader_t*)&instance);
    
    engine3D_shader_addUniform("transform", (engine3D_shader_t*)&instance);
    engine3D_shader_addUniform("color", (engine3D_shader_t*)&instance);
    
    isLoaded = true;
  }
  
  return &instance;
}

void engine3D_basicShader_destroy(engine3D_basicShader_t *const shader) {
  engine3D_shader_destroy((engine3D_shader_t*)shader);
}

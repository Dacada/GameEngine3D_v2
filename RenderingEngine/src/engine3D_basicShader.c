#include <engine3D_basicShader.h>
#include <engine3D_shader.h>
#include <engine3D_renderUtil.h>

static engine3D_basicShader_t instance;
static bool isLoaded = false;

engine3D_basicShader_t *engine3D_basicShader_getInstance(void) {
  if (!isLoaded) {
	engine3D_shader_init((engine3D_shader_t*)&instance);

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

void engine3D_basicShader_updateUniforms(engine3D_basicShader_t * const shader, const engine3D_matrix4f_t *const worldMatrix, const engine3D_matrix4f_t *projectedMatrix, const engine3D_material_t *const material) {
	(void)worldMatrix;

	if (material->texture != NULL)
		engine3D_texture_bind(material->texture);
	else
		engine3D_renderUtil_unbindTextures();

	engine3D_shader_setUniformMat4f("transform", projectedMatrix, (engine3D_shader_t*)shader);
	engine3D_shader_setUniformVec3f("color", material->color, (engine3D_shader_t*)shader);
}

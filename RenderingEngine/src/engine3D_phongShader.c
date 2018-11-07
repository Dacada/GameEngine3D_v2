#include <engine3D_phongShader.h>
#include <engine3D_shader.h>
#include <engine3D_renderUtil.h>
#include <Base/engine3D_transform.h>
#include <string.h>

engine3D_vector3f_t engine3D_phongShader_ambientLight;
engine3D_phongShader_directionalLight_t engine3D_phongShader_directionalLight;
engine3D_phongShader_pointLight_t engine3D_phongShader_pointLights[ENGINE3D_PHONGSHADER_MAXPOINTLIGHTS];
engine3D_phongShader_spotLight_t engine3D_phongShader_spotLights[ENGINE3D_PHONGSHADER_MAXSPOTLIGHTS];
size_t engine3D_phongShader_numberOfPointLights = 0;
size_t engine3D_phongShader_numberOfSpotLights = 0;

engine3D_phongShader_t *engine3D_phongShader_init(engine3D_phongShader_t *const shader) {
	engine3D_shader_init((engine3D_shader_t*)shader);

	engine3D_shader_addVertexShaderFromFile("phongVertex.vs", (engine3D_shader_t*)shader);
	engine3D_shader_addFragmentShaderFromFile("phongFragment.fs", (engine3D_shader_t*)shader);
	engine3D_shader_compile((engine3D_shader_t*)shader);

	engine3D_shader_addUniform("transform", (engine3D_shader_t*)shader);
	engine3D_shader_addUniform("transformProjected", (engine3D_shader_t*)shader);
	engine3D_shader_addUniform("baseColor", (engine3D_shader_t*)shader);
	engine3D_shader_addUniform("ambientLight", (engine3D_shader_t*)shader);

	engine3D_shader_addUniform("directionalLight.base.color", (engine3D_shader_t*)shader);
	engine3D_shader_addUniform("directionalLight.base.intensity", (engine3D_shader_t*)shader);
	engine3D_shader_addUniform("directionalLight.direction", (engine3D_shader_t*)shader);

	engine3D_shader_addUniform("specularIntensity", (engine3D_shader_t*)shader);
	engine3D_shader_addUniform("specularPower", (engine3D_shader_t*)shader);
	engine3D_shader_addUniform("eyePos", (engine3D_shader_t*)shader);

	for (size_t i = 0; i < ENGINE3D_PHONGSHADER_MAXPOINTLIGHTS; i++) {
		char str[128], base[64];
		sprintf(base, "pointLights[%lu]", i);

		strncpy(str, base, 128);
		str[127] = 0;
		strncat(str, ".base.color", 128);
		str[127] = 0;
		engine3D_shader_addUniform(str, (engine3D_shader_t*)shader);

		strncpy(str, base, 64);
		str[127] = 0;
		strncat(str, ".base.intensity", 128);
		str[127] = 0;
		engine3D_shader_addUniform(str, (engine3D_shader_t*)shader);

		strncpy(str, base, 64);
		str[127] = 0;
		strncat(str, ".atten.constant", 128);
		str[127] = 0;
		engine3D_shader_addUniform(str, (engine3D_shader_t*)shader);

		strncpy(str, base, 64);
		str[127] = 0;
		strncat(str, ".atten.linear", 128);
		str[127] = 0;
		engine3D_shader_addUniform(str, (engine3D_shader_t*)shader);

		strncpy(str, base, 64);
		str[127] = 0;
		strncat(str, ".atten.exponent", 128);
		str[127] = 0;
		engine3D_shader_addUniform(str, (engine3D_shader_t*)shader);

		strncpy(str, base, 64);
		str[127] = 0;
		strncat(str, ".position", 128);
		str[127] = 0;
		engine3D_shader_addUniform(str, (engine3D_shader_t*)shader);

		strncpy(str, base, 64);
		str[127] = 0;
		strncat(str, ".range", 128);
		str[127] = 0;
		engine3D_shader_addUniform(str, (engine3D_shader_t*)shader);
	}

	for (size_t i = 0; i < ENGINE3D_PHONGSHADER_MAXPOINTLIGHTS; i++) {
		char str[128], base[64];
		sprintf(base, "spotLights[%lu]", i);

		strncpy(str, base, 128);
		str[127] = 0;
		strncat(str, ".pointLight.base.color", 128);
		str[127] = 0;
		engine3D_shader_addUniform(str, (engine3D_shader_t*)shader);

		strncpy(str, base, 64);
		str[127] = 0;
		strncat(str, ".pointLight.base.intensity", 128);
		str[127] = 0;
		engine3D_shader_addUniform(str, (engine3D_shader_t*)shader);

		strncpy(str, base, 64);
		str[127] = 0;
		strncat(str, ".pointLight.atten.constant", 128);
		str[127] = 0;
		engine3D_shader_addUniform(str, (engine3D_shader_t*)shader);

		strncpy(str, base, 64);
		str[127] = 0;
		strncat(str, ".pointLight.atten.linear", 128);
		str[127] = 0;
		engine3D_shader_addUniform(str, (engine3D_shader_t*)shader);

		strncpy(str, base, 64);
		str[127] = 0;
		strncat(str, ".pointLight.atten.exponent", 128);
		str[127] = 0;
		engine3D_shader_addUniform(str, (engine3D_shader_t*)shader);

		strncpy(str, base, 64);
		str[127] = 0;
		strncat(str, ".pointLight.position", 128);
		str[127] = 0;
		engine3D_shader_addUniform(str, (engine3D_shader_t*)shader);

		strncpy(str, base, 64);
		str[127] = 0;
		strncat(str, ".pointLight.range", 128);
		str[127] = 0;
		engine3D_shader_addUniform(str, (engine3D_shader_t*)shader);

		strncpy(str, base, 64);
		str[127] = 0;
		strncat(str, ".direction", 128);
		str[127] = 0;
		engine3D_shader_addUniform(str, (engine3D_shader_t*)shader);

		strncpy(str, base, 64);
		str[127] = 0;
		strncat(str, ".cutoff", 128);
		str[127] = 0;
		engine3D_shader_addUniform(str, (engine3D_shader_t*)shader);
	}

	return shader;
}

void engine3D_phongShader_destroy(const engine3D_phongShader_t * const shader) {
	engine3D_shader_destroy((engine3D_shader_t*)shader);
}

void engine3D_phongShader_updateUniforms(engine3D_phongShader_t * const shader, const engine3D_matrix4f_t *const worldMatrix, const engine3D_matrix4f_t *projectedMatrix, const engine3D_material_t *const material, const engine3D_vector3f_t pos) {
	if (material->texture != NULL)
		engine3D_texture_bind(material->texture);
	else
		engine3D_renderUtil_unbindTextures();

	engine3D_shader_setUniformMat4f("transform", worldMatrix, (engine3D_shader_t*)shader);
	engine3D_shader_setUniformMat4f("transformProjected", projectedMatrix, (engine3D_shader_t*)shader);
	engine3D_shader_setUniformVec3f("baseColor", material->color, (engine3D_shader_t*)shader);

	engine3D_shader_setUniformVec3f("ambientLight", engine3D_phongShader_ambientLight, (engine3D_shader_t*)shader);
	engine3D_phongShader_setUniformDirectionalLight("directionalLight", &engine3D_phongShader_directionalLight, shader);

	for (size_t i = 0; i < engine3D_phongShader_numberOfPointLights; i++) {
		char base[64];
		sprintf(base, "pointLights[%lu]", i);
		engine3D_phongShader_setUniformPointLight(base, &engine3D_phongShader_pointLights[i], shader);
	}

	for (size_t i = 0; i < engine3D_phongShader_numberOfSpotLights; i++) {
		char base[64];
		sprintf(base, "spotLights[%lu]", i);
		engine3D_phongShader_setUniformSpotLight(base, &engine3D_phongShader_spotLights[i], shader);
	}

	engine3D_shader_setUniformf("specularIntensity", material->specularIntensity, (engine3D_shader_t*)shader);
	engine3D_shader_setUniformf("specularPower", material->specularPower, (engine3D_shader_t*)shader);
	engine3D_shader_setUniformVec3f("eyePos", pos, (engine3D_shader_t*)shader);
}

void engine3D_phongShader_setUniformBaseLight(const char *const uniform, const engine3D_phongShader_baseLight_t *const value, const engine3D_phongShader_t *const shader) {
	char name[2048];

	strncpy(name, uniform, 2048);
	strncat(name, ".color", 2048);
	engine3D_shader_setUniformVec3f(name, value->color, (engine3D_shader_t*)shader);

	strncpy(name, uniform, 2048);
	strncat(name, ".intensity", 2048);
	engine3D_shader_setUniformf(name, value->intensity, (engine3D_shader_t*)shader);
}

void engine3D_phongShader_setUniformDirectionalLight(const char *const uniform, const engine3D_phongShader_directionalLight_t *const value, const engine3D_phongShader_t *const shader) {
	char name[2048];

	strncpy(name, uniform, 2048);
	strncat(name, ".base", 2048);
	engine3D_phongShader_setUniformBaseLight(name, &value->base, shader);

	strncpy(name, uniform, 2048);
	strncat(name, ".direction", 2048);
	engine3D_shader_setUniformVec3f(name, value->direction, (engine3D_shader_t*)shader);
}

void engine3D_phongShader_setUniformPointLight(const char *const uniform, const engine3D_phongShader_pointLight_t *const value, const engine3D_phongShader_t *const shader) {
	char name[2048];

	strncpy(name, uniform, 2048);
	strncat(name, ".base", 2048);
	engine3D_phongShader_setUniformBaseLight(name, &value->base, shader);

	strncpy(name, uniform, 2048);
	strncat(name, ".atten.constant", 2048);
	engine3D_shader_setUniformf(name, value->atten.constant, (engine3D_shader_t*)shader);

	strncpy(name, uniform, 2048);
	strncat(name, ".atten.linear", 2048);
	engine3D_shader_setUniformf(name, value->atten.linear, (engine3D_shader_t*)shader);

	strncpy(name, uniform, 2048);
	strncat(name, ".atten.exponent", 2048);
	engine3D_shader_setUniformf(name, value->atten.exponent, (engine3D_shader_t*)shader);

	strncpy(name, uniform, 2048);
	strncat(name, ".position", 2048);
	engine3D_shader_setUniformVec3f(name, value->position, (engine3D_shader_t*)shader);

	strncpy(name, uniform, 2048);
	strncat(name, ".range", 2048);
	engine3D_shader_setUniformf(name, value->range, (engine3D_shader_t*)shader);
}

void engine3D_phongShader_setUniformSpotLight(const char *const uniform, const engine3D_phongShader_spotLight_t *const value, const engine3D_phongShader_t *const shader) {
	char name[2048];

	strncpy(name, uniform, 2048);
	strncat(name, ".pointLight", 2048);
	engine3D_phongShader_setUniformPointLight(name, &value->pointLight, shader);

	strncpy(name, uniform, 2048);
	strncat(name, ".direction", 2048);
	engine3D_shader_setUniformVec3f(name, value->direction, (engine3D_shader_t*)shader);

	strncpy(name, uniform, 2048);
	strncat(name, ".cutoff", 2048);
	engine3D_shader_setUniformf(name, value->cutoff, (engine3D_shader_t*)shader);
}

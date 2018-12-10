#ifndef ENGINE3D_SHADER_H
#define ENGINE3D_SHADER_H

#include "engine3D_material.h"
#include "engine3D_camera.h"
#include "engine3D_baseLight.h"
#include "engine3D_directionalLight.h"
#include "engine3D_pointLight.h"
#include "engine3D_spotLight.h"
#include <Base/engine3D_vector.h>
#include <Base/engine3D_strToIntMap.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

typedef struct engine3D_shader_t {
  GLuint program;
  engine3D_strToIntMap_t *uniforms;
  void(*updateUniforms)(struct engine3D_shader_t *const,
			const engine3D_transform_t *const,
			const engine3D_camera_t *const,
			const engine3D_material_t *const);
} engine3D_shader_t;

engine3D_shader_t *engine3D_shader_init(engine3D_shader_t *const shader);

void engine3D_shader_destroy(const engine3D_shader_t *const shader);

engine3D_shader_t *engine3D_shader_addVertexShader(const char *const text, engine3D_shader_t * const shader);

engine3D_shader_t *engine3D_shader_addGeometryShader(const char *const text, engine3D_shader_t * const shader);

engine3D_shader_t *engine3D_shader_addFragmentShader(const char *const text, engine3D_shader_t * const shader);

engine3D_shader_t *engine3D_shader_addVertexShaderFromFile(const char *const text, engine3D_shader_t * const shader);

engine3D_shader_t *engine3D_shader_addGeometryShaderFromFile(const char *const text, engine3D_shader_t * const shader);

engine3D_shader_t *engine3D_shader_addFragmentShaderFromFile(const char *const text, engine3D_shader_t * const shader);

void engine3D_shader_compile(const engine3D_shader_t * const shader);

void engine3D_shader_bind(const engine3D_shader_t * const shader);

void engine3D_shader_addUniform(const char *const uniform, const engine3D_shader_t *const shader);

void engine3D_shader_setUniformi(const char *const uniform, const int value, const engine3D_shader_t *const shader);

void engine3D_shader_setUniformf(const char *const uniform, const float value, const engine3D_shader_t *const shader);

void engine3D_shader_setUniformVec3f(const char *const uniform, const engine3D_vector3f_t value, const engine3D_shader_t *const shader);

void engine3D_shader_setUniformMat4f(const char *const uniform, const engine3D_matrix4f_t *const value, const engine3D_shader_t *const shader);

void engine3D_shader_setUniformBaseLight(const char *const uniform, const engine3D_baseLight_t *const value, const engine3D_shader_t *const shader);

void engine3D_shader_setUniformDirectionalLight(const char *const uniform, const engine3D_directionalLight_t *const value, const engine3D_shader_t *const shader);

void engine3D_shader_setUniformPointLight(const char *const uniform, const engine3D_pointLight_t *const value, const engine3D_shader_t *const shader);

void engine3D_shader_setUniformAttenuation(const char *const uniform, const engine3D_attenuation_t *const value, const engine3D_shader_t *const shader);

void engine3D_shader_setUniformSpotLight(const char *const uniform, const engine3D_spotLight_t *const value, const engine3D_shader_t *const shader);

#endif /* ENGINE3D_SHADER_H */

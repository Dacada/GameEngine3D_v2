#include <Base/engine3D_util.h>
#include <engine3D_shader.h>
#include <stdlib.h>
#include <string.h>

static void addProgram(const char *const text, engine3D_shader_t * const shader, GLenum type) {
	GLuint shaderId = glCreateShader(type);
	if (shader == 0) {
		engine3D_util_bail("shader creation failed");
	}

	glShaderSource(shaderId, 1, &text, NULL);
	glCompileShader(shaderId);

	GLint status;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		char infoLog[1024];
		glGetShaderInfoLog(shaderId, 1024, NULL, infoLog);
		fputs(infoLog, stderr);
		engine3D_util_quit("shader compilation failed");
	}

	glAttachShader(shader->program, shaderId);
}


engine3D_shader_t *engine3D_shader_init(engine3D_shader_t * const shader) {
	shader->uniforms = engine3D_strToIntMap_new();
	engine3D_strToIntMap_init(shader->uniforms);
	shader->updateUniforms = NULL;

	shader->program = glCreateProgram();
	if (shader->program == 0)
	{
		engine3D_util_bail("shader program creation failed");
	}
	return shader;
}

void engine3D_shader_destroy(const engine3D_shader_t *const shader) {
	engine3D_strToIntMap_destroy(shader->uniforms);
	free(shader->uniforms);
}

static char *loadShader(const char *const filename, char *const text, size_t size) {
	char filepath[256];
	strncpy(filepath, engine3D_util_resourcesPath, 256);
	strncat(filepath, "shaders/", 256);
	strncat(filepath, filename, 128);

	FILE *f = fopen(filepath, "r");
	if (f == NULL) {
		perror("fopen");
		engine3D_util_quit("failed to load shader");
	}

	size_t s = fread(text, sizeof(char), size, f);
	int err;
	if ((err = ferror(f)) != 0) {
		engine3D_util_errPrintf("fread: error %d", err);
		engine3D_util_quit("failed to load shader");
	}
	text[s] = '\0'; // Ensure it's null terminated

	fclose(f);

	return text;
}

engine3D_shader_t *engine3D_shader_addVertexShader(const char *const text, engine3D_shader_t * const shader) {
	addProgram(text, shader, GL_VERTEX_SHADER);
	return shader;
}

engine3D_shader_t *engine3D_shader_addGeometryShader(const char *const text, engine3D_shader_t * const shader) {
	addProgram(text, shader, GL_GEOMETRY_SHADER);
	return shader;
}

engine3D_shader_t *engine3D_shader_addFragmentShader(const char *const text, engine3D_shader_t * const shader) {
	addProgram(text, shader, GL_FRAGMENT_SHADER);
	return shader;
}

engine3D_shader_t *engine3D_shader_addVertexShaderFromFile(const char *const text, engine3D_shader_t * const shader) {
	char shaderText[65536];
	loadShader(text, shaderText, 65536);
	addProgram(shaderText, shader, GL_VERTEX_SHADER);
	return shader;
}

engine3D_shader_t *engine3D_shader_addGeometryShaderFromFile(const char *const text, engine3D_shader_t * const shader) {
	char shaderText[65536];
	loadShader(text, shaderText, 65536);
	addProgram(shaderText, shader, GL_GEOMETRY_SHADER);
	return shader;
}

engine3D_shader_t *engine3D_shader_addFragmentShaderFromFile(const char *const text, engine3D_shader_t * const shader) {
	char shaderText[65536];
	loadShader(text, shaderText, 65536);
	addProgram(shaderText, shader, GL_FRAGMENT_SHADER);
	return shader;
}

void engine3D_shader_compile(const engine3D_shader_t * const shader) {
	glLinkProgram(shader->program);

	GLint status;
	glGetProgramiv(shader->program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {
		char infoLog[1024];
		glGetProgramInfoLog(shader->program, 1024, NULL, infoLog);
		fputs(infoLog, stderr);
		engine3D_util_quit("shader linking failed");
	}

	glValidateProgram(shader->program);

	glGetProgramiv(shader->program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {
		char infoLog[1024];
		glGetProgramInfoLog(shader->program, 1024, NULL, infoLog);
		fputs(infoLog, stderr);
		engine3D_util_quit("shader validation failed");
	}
}

void engine3D_shader_bind(const engine3D_shader_t * const shader) {
	glUseProgram(shader->program);
}

void engine3D_shader_addUniform(const char *const uniform, const engine3D_shader_t *const shader) {
	GLint uniformLocation = glGetUniformLocation(shader->program, uniform);

	if (uniformLocation == -1) {
		engine3D_util_bail("could not find uniform location");
	}

	engine3D_strToIntMap_add(shader->uniforms, uniform, uniformLocation);
}

void engine3D_shader_setUniformi(const char * const uniform, const int value, const engine3D_shader_t *const shader) {
	int location = engine3D_strToIntMap_get(shader->uniforms, uniform);
	glUniform1i(location, value);
}

void engine3D_shader_setUniformf(const char * const uniform, const float value, const engine3D_shader_t *const shader) {
	int location = engine3D_strToIntMap_get(shader->uniforms, uniform);
	glUniform1f(location, value);
}

void engine3D_shader_setUniformVec3f(const char *const uniform, const engine3D_vector3f_t value, const engine3D_shader_t *const shader) {
	int location = engine3D_strToIntMap_get(shader->uniforms, uniform);
	glUniform3f(location, value.x, value.y, value.z);
}

void engine3D_shader_setUniformMat4f(const char *const uniform, const engine3D_matrix4f_t *const value, const engine3D_shader_t *const shader) {
	int location = engine3D_strToIntMap_get(shader->uniforms, uniform);
	glUniformMatrix4fv(location, 1, GL_TRUE, (float*)value->mat);
}

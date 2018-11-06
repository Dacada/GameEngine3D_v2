#include <engine3D_renderUtil.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

#include <stdbool.h>

void engine3D_renderUtil_clearScreen(void) {
	// TODO: Stencil Buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void engine3D_renderUtil_setTextures(const bool enabled) {
	if (enabled)
		glEnable(GL_TEXTURE_2D);
	else
		glDisable(GL_TEXTURE_2D);
}

void engine3D_renderUtils_setClearColor(const engine3D_vector3f_t color) {
	glClearColor(color.x, color.y, color.z, 1);
}

void engine3D_renderUtil_initGraphics(void) {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_CLAMP);
	glEnable(GL_TEXTURE_2D);
}

void engine3D_renderUtil_unbindTextures(void) {
	glBindTexture(GL_TEXTURE_2D, 0);
}

const char *engine3D_renderUtil_getOpenGLVersion(void) {
	return (char*)glGetString(GL_VERSION);
}

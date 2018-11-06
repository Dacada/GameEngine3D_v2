#include <engine3D_texture.h>
#include <engine3D_resourceLoader.h>

engine3D_texture_t engine3D_texture_loadFromFile(const char *const filename) {
	engine3D_texture_t t;
	engine3D_resourceLoader_loadTexture(filename, &t);
	return t;
}

void engine3D_texture_bind(engine3D_texture_t *const texture) {
	glBindTexture(GL_TEXTURE_2D, texture->id);
}

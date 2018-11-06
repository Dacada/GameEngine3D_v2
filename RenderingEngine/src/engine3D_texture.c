#include <Base/engine3D_util.h>
#include <engine3D_texture.h>
#include <FreeImage.h>
#include <string.h>

static void loadTexture(const char *const filename, engine3D_texture_t *const texture) {
	char filepath[256];
	strncpy(filepath, engine3D_util_resourcesPath, 256);
	strncat(filepath, "textures/", 256);
	strncat(filepath, filename, 128);

	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	FIBITMAP *dib = NULL;
	BYTE* bits;
	unsigned int width, height;

	fif = FreeImage_GetFileType(filepath, 0);
	if (fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(filepath);
	if (fif == FIF_UNKNOWN)
		engine3D_util_quit("attempt to load texture of unknown image type");

	if (FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, filepath, 0);

	if (!dib)
		engine3D_util_quit("failed to load image for texture");

	FIBITMAP *dib32 = FreeImage_ConvertTo32Bits(dib);
	FreeImage_Unload(dib);

	bits = FreeImage_GetBits(dib32);
	width = FreeImage_GetWidth(dib32);
	height = FreeImage_GetHeight(dib32);
	if (bits == 0 || width == 0 || height == 0)
		engine3D_util_quit("failed to load image data for texture");

	glGenTextures(1, &texture->id);
	glBindTexture(GL_TEXTURE_2D, texture->id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, bits);

	FreeImage_Unload(dib32);
}

engine3D_texture_t engine3D_texture_loadFromFile(const char *const filename) {
	engine3D_texture_t t;
	loadTexture(filename, &t);
	return t;
}

void engine3D_texture_bind(engine3D_texture_t *const texture) {
	glBindTexture(GL_TEXTURE_2D, texture->id);
}

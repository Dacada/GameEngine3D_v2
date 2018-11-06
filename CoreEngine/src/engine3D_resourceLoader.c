#include <engine3D_resourceLoader.h>
#include <engine3D_util.h>
#include <engine3D_growingArray.h>
#include <engine3D_mesh.h>
#include <engine3D_vertex.h>

#include <FreeImage.h>

#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>

const char *resourcesPath = ENGINE3D_RES_PATH;
void engine3D_resourceLoader_setResPath(const char *path) {
	resourcesPath = path;
}

char *engine3D_resourceLoader_loadShader(const char *const filename, char *const text, size_t size) {
	char filepath[256];
	strncpy(filepath, resourcesPath, 256);
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

// Read one line from stream. If line is greater than maxSize return -2.
// If error is found on stream or eof, return -1
// Otherwise return 0;
static int readLine(FILE *stream, char buff[], size_t maxSize) {
	if (ferror(stream) || feof(stream)) {
		return -1;
	}

	if (fgets(buff, maxSize, stream) == NULL) {
		return -1;
	}

	char *ptr = strchr(buff, '\n');
	if (ptr != NULL) {
		*ptr = '\0';
		return 0;
	}
	else {
		if (feof(stream))
			return -1;
		else
			return -2;
	}
}

static void skipWhitespace(char **buff) {
	char *b = *buff;
	while (*b != '\0' && isspace(*b) != 0) {
		b++;
	}
	*buff = b;
}

static char *getNextToken(char *ptr, char buff[], size_t len) {
	skipWhitespace(&ptr);

	if (*ptr == '\0') {
		buff[0] = '\n';
		buff[1] = '\0';
		return ptr;
	}

	for (size_t i = 0; i < len; i++) {
		if (isspace(*ptr)) {
			buff[i] = '\0';
			return ptr;
		}

		buff[i] = *ptr;
		ptr++;
	}

	return NULL;
}

static float readNextFloat(char **ptr) {
	char *tmp;
	errno = 0;
	float num = strtof(*ptr, &tmp);

	if (errno != 0) {
		perror("strtof");
		engine3D_util_quit("attempt to load invalid .obj file (error reading float)");
	}

	if (*ptr == tmp) {
		engine3D_util_quit("attempt to load invalid .obj file (could not find float)");
	}

	*ptr = tmp;
	return num;
}

static long readNextLong(char **ptr) {
	char *tmp;
	errno = 0;
	long num = strtol(*ptr, &tmp, 10);

	if (errno != 0) {
		perror("strtol");
		engine3D_util_quit("attempt to load invalid .obj file (error reading long)");
	}

	if (*ptr == tmp) {
		engine3D_util_quit("attempt to load invalid .obj file (could not find long)");
	}

	*ptr = tmp;

	return num;
}

static void readFaces(char *input, int faces[3][3], size_t iv, size_t itv, size_t inv) {
	size_t i, j;

	for (i = 0; i < 9; i++) {
		faces[i / 3][i % 3] = -1;
	}

	while (isspace(*input)) input++;

	i = j = 0;
	while (*input != '\0') {
		if (isspace(*input)) {
			j++;
			i = 0;
			while (isspace(*input)) input++;
		}
		else if (*input == '/') {
			i++;
			input++;
		}
		else {
			long n = readNextLong(&input);

			size_t lastIndex;
			if (i == 0) {
				lastIndex = iv;
			}
			else if (i == 1) {
				lastIndex = itv;
			}
			else if (i == 2) {
				lastIndex = inv;
			}
			else {
				engine3D_util_quit("attempt to load invalid .obj file (too many items in face tuple)");
			}

			if (n > 0) {
				n -= 1;
			}
			else if (n < 0) {
				n = lastIndex - (n + 1);
			}
			else {
				engine3D_util_quit("attempt to load invalid .obj file (invalid index: 0)");
			}

			if (n > INT_MAX) engine3D_util_quit("attempt to load invalid .obj file (index too positive)");
			if (n < 0) engine3D_util_quit("attempt to load invalid .obj file (index too negative)");

			faces[j][i] = (int)n;
		}
	}
}

// indices is an array of arrays of structs used as the underlying data of a hash map that maps a face tuple (vertex, texture coord, normal) to an index
// struct fields meaning: the first three are the tuple, the index field is the index this tupple is mapped to, the last field is a pointer to the next
// it's an array of arrays because there might be hash collisions
struct bucket { int faceV; int faceT; int faceN; size_t index; struct bucket *next; };
struct bucket *indices[0x1000];
size_t lastIndex;

size_t getFaceKey(int face[3]) {
	size_t result = 0;

	for (int i = 0; i < 3; i++) {
		result += face[i];
		result %= 0x1000;
		result *= 5113;
		result %= 0x1000;
	}

	return result;
}

void initSeenIndex() {
	for (int i = 0; i < 0x1000; i++) {
		if (indices[i] != NULL) {
			struct bucket *b = indices[i];
			struct bucket *next;
			while (b != NULL) {
				next = b->next;
				free(b);
				b = next;
			}
		}
		indices[i] = NULL;
	}
	lastIndex = 0;
}

bool getSeenIndex(int face[3], size_t *seenIndex) {
	size_t key = getFaceKey(face);
	struct bucket *b = indices[key];
	if (b == NULL) {
		return false;
	}
	else {
		while ((b = b->next) != NULL) {
			if (b->faceV == face[0] && b->faceT == face[1] && b->faceN == face[2]) {
				*seenIndex = b->index;
				return true;
			}
		}
		return false;
	}
}

size_t setSeenIndex(int face[3]) {
	size_t key = getFaceKey(face);
	struct bucket *b = indices[key];

	if (b == NULL) {
		b = indices[key] = engine3D_util_safeMalloc(sizeof(struct bucket));
	}
	else {
		struct bucket *next = b->next;
		while (next != NULL) {
			b = next;
			next = b->next;
		}
	}

	b->faceV = face[0];
	b->faceT = face[1];
	b->faceN = face[2];
	b->index = lastIndex;
	b->next = NULL;
	return lastIndex++;
}

void engine3D_resourceLoader_loadMesh(const char *const filename, engine3D_mesh_t *const mesh) {
	char filepath[256];
	strncpy(filepath, resourcesPath, 256);
	strncat(filepath, "models/", 256);
	strncat(filepath, filename, 128);

	initSeenIndex();

	engine3D_growingArray_t vertices, indices, vs, vts, vns;
	engine3D_growingArray_init(&vertices, sizeof(engine3D_vertex_t), 4);
	engine3D_growingArray_init(&indices, sizeof(unsigned int), 4);
	engine3D_growingArray_init(&vs, sizeof(engine3D_vector3f_t), 4);
	engine3D_growingArray_init(&vts, sizeof(engine3D_vector2f_t), 4);
	engine3D_growingArray_init(&vns, sizeof(engine3D_vector3f_t), 4);

	size_t filenameLen = strlen(filepath);
	if (filenameLen < 4 || strncmp(filepath + filenameLen - 4, ".obj", 4) != 0) {
		engine3D_util_quit("attempt to load unsupported mesh file format (file name doesn't end with '.obj'");
	}

	FILE *f = fopen(filepath, "r");
	if (f == NULL) {
		perror("fopen");
		engine3D_util_quit("failed to load mesh file");
	}

	int ret;
	char lineBuff[1024];
	while ((ret = readLine(f, lineBuff, 1024)) == 0) {
		char *current = lineBuff;
		char token[256];

		current = getNextToken(current, token, 256);
		if (current == NULL) {
			engine3D_util_quit("attempt to load invalid .obj file (invalid token)");
		}

		if (strncmp(token, "#", 2) == 0 || strncmp(token, "\n", 2) == 0) {
			continue;
		}
		else if (strncmp(token, "v", 2) == 0) {
			float coords[3];
			coords[0] = readNextFloat(&current);
			coords[1] = readNextFloat(&current);
			coords[2] = readNextFloat(&current);
			while (!isspace(*current) && *current != '\0') current++;
			if (*current != '\0')
				engine3D_util_debugPrintf("reading .obj file: ignoring optional w element of vertex");

			engine3D_vector3f_t *currentVs = engine3D_growingArray_add(&vs);
			currentVs->x = coords[0];
			currentVs->y = coords[1];
			currentVs->z = coords[2];
		}
		else if (strncmp(token, "vt", 3) == 0) {
			float coords[2];
			coords[0] = readNextFloat(&current);
			coords[1] = readNextFloat(&current);
			while (!isspace(*current) && *current != '\0') current++;
			if (*current != '\0')
				engine3D_util_debugPrintf("reading .obj file: ignoring optional w element of texture");

			engine3D_vector2f_t *currentVts = engine3D_growingArray_add(&vts);
			currentVts->x = coords[0];
			currentVts->y = coords[1];
		}
		else if (strncmp(token, "vn", 3) == 0) {
			float coords[3];
			coords[0] = readNextFloat(&current);
			coords[1] = readNextFloat(&current);
			coords[2] = readNextFloat(&current);

			engine3D_vector3f_t *currentVns = engine3D_growingArray_add(&vns);
			currentVns->x = coords[0];
			currentVns->y = coords[1];
			currentVns->z = coords[2];
		}
		else if (strncmp(token, "f", 2) == 0) {
			int faces[3][3];
			readFaces(current, faces, engine3D_growingArray_length(&vs), engine3D_growingArray_length(&vts), engine3D_growingArray_length(&vns));

			for (int i = 0; i < 3; i++)
			{
				size_t seenIndex;
				bool hasBeenSeen = getSeenIndex(faces[i], &seenIndex);
				if (!hasBeenSeen) {
					seenIndex = setSeenIndex(faces[i]);

					engine3D_vertex_t *currentVertex = engine3D_growingArray_add(&vertices);

					engine3D_vector3f_t *vsArray = engine3D_growingArray_finish(&vs, false);
					currentVertex->vec.x = vsArray[faces[i][0]].x;
					currentVertex->vec.y = vsArray[faces[i][0]].y;
					currentVertex->vec.z = vsArray[faces[i][0]].z;
					if (faces[i][1] >= 0) {
						engine3D_vector2f_t *vtsArray = engine3D_growingArray_finish(&vts, false);
						currentVertex->texCoord.x = vtsArray[faces[i][1]].x;
						currentVertex->texCoord.y = vtsArray[faces[i][1]].y;
					}
					if (faces[i][2] >= 0) {
						engine3D_vector3f_t *vnsArray = engine3D_growingArray_finish(&vns, false);
						currentVertex->normal.x = vnsArray[faces[i][2]].x;
						currentVertex->normal.y = vnsArray[faces[i][2]].y;
						currentVertex->normal.z = vnsArray[faces[i][2]].z;
					}
				}

				unsigned int *currentIndex = engine3D_growingArray_add(&indices);
				*currentIndex = seenIndex;
			}
		}
		else {
			engine3D_util_debugPrintf("reading .obj file: ignoring token: %s", token);
		}
	}

	if (ret == -2) {
		engine3D_util_quit("attempt to load invalid .obj file (file's lines detected as too long)");
	}
	else {
		int err = ferror(f);
		if (err != 0) {
			engine3D_util_errPrintf("reading file: error %d", err);
			engine3D_util_quit("failed to load mesh file");
		}
	}

	fclose(f);

	engine3D_mesh_init(mesh);
	engine3D_mesh_addVertices(mesh, engine3D_growingArray_finish(&vertices, false), engine3D_growingArray_length(&vertices), engine3D_growingArray_finish(&indices, false), engine3D_growingArray_length(&indices), false);

	engine3D_growingArray_discard(&vs);
	engine3D_growingArray_discard(&vts);
	engine3D_growingArray_discard(&vns);
	engine3D_growingArray_discard(&vertices);
	engine3D_growingArray_discard(&indices);
}

void engine3D_resourceLoader_loadTexture(const char *const filename, engine3D_texture_t *const texture) {
	char filepath[256];
	strncpy(filepath, resourcesPath, 256);
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

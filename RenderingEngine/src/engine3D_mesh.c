#include <Base/engine3D_growingArray.h>
#include <Base/engine3D_util.h>
#include <engine3D_mesh.h>
#include <engine3D_vertex.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

static void calcNormals(engine3D_vertex_t vertices[], size_t vertices_len, unsigned int indices[], size_t indices_len) {
	for (size_t i = 0; i < indices_len; i += 3) {
		int i0 = indices[i];
		int i1 = indices[i + 1];
		int i2 = indices[i + 2];

		engine3D_vector3f_t v1, v2, normal;
		v1 = engine3D_vector3f_sub(vertices[i1].vec, vertices[i0].vec);
		v2 = engine3D_vector3f_sub(vertices[i2].vec, vertices[i0].vec);
		normal = engine3D_vector3f_normalized(engine3D_vector3f_cross(v1, v2));

		vertices[i0].normal = engine3D_vector3f_add(vertices[i0].normal, normal);
		vertices[i1].normal = engine3D_vector3f_add(vertices[i1].normal, normal);
		vertices[i2].normal = engine3D_vector3f_add(vertices[i2].normal, normal);
	}

	for (size_t i = 0; i < vertices_len; i++) {
		engine3D_vector3f_normalize(&vertices[i].normal);
	}
}

engine3D_mesh_t * engine3D_mesh_init(engine3D_mesh_t * const mesh) {
	glGenBuffers(1, &mesh->vbo);
	glGenBuffers(1, &mesh->ibo);
	mesh->len_vbo = 0;
	mesh->len_ibo = 0;
	return mesh;
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

static size_t getFaceKey(int face[3]) {
	size_t result = 0;

	for (int i = 0; i < 3; i++) {
		result += face[i];
		result %= 0x1000;
		result *= 5113;
		result %= 0x1000;
	}

	return result;
}

static void initSeenIndex() {
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

static bool getSeenIndex(int face[3], size_t *seenIndex) {
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

static size_t setSeenIndex(int face[3]) {
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

static void loadMesh(const char *const filename, engine3D_mesh_t *const mesh) {
	char filepath[256];
	strncpy(filepath, engine3D_util_resourcesPath, 256);
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

engine3D_mesh_t *engine3D_mesh_initFromFile(const char *const filename, engine3D_mesh_t *const mesh) {
  loadMesh(filename, mesh);
	return mesh;
}

engine3D_mesh_t * engine3D_mesh_addVertices(engine3D_mesh_t * const mesh, engine3D_vertex_t vertices[], size_t vertices_len, unsigned int indices[], const size_t indices_len, const bool doCalcNormals) {
	if (doCalcNormals)
		calcNormals(vertices, vertices_len, indices, indices_len);

	mesh->len_vbo = vertices_len;
	mesh->len_ibo = indices_len;

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices_len * sizeof(engine3D_vertex_t), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_len * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	return mesh;
}

void engine3D_mesh_draw(const engine3D_mesh_t * const mesh) {
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(engine3D_vertex_t), (void*)offsetof(engine3D_vertex_t, vec));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(engine3D_vertex_t), (void*)offsetof(engine3D_vertex_t, texCoord));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(engine3D_vertex_t), (void*)offsetof(engine3D_vertex_t, normal));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ibo);
	glDrawElements(GL_TRIANGLES, mesh->len_ibo, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

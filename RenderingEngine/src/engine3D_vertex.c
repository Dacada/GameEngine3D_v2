#include <engine3D_vertex.h>

void engine3D_vertex_initZero(engine3D_vertex_t *const vertex) {
	vertex->vec.x = 0;
	vertex->vec.y = 0;
	vertex->vec.z = 0;
	vertex->texCoord.x = 0;
	vertex->texCoord.y = 0;
	vertex->normal.x = 0;
	vertex->normal.y = 0;
	vertex->normal.z = 0;
}

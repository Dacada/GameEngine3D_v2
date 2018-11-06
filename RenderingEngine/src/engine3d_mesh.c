#include <engine3D_mesh.h>
#include <engine3D_vertex.h>
#include <engine3D_resourceLoader.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

#include <stdbool.h>

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

engine3D_mesh_t *engine3D_mesh_initFromFile(const char *const filename, engine3D_mesh_t *const mesh) {
	engine3D_resourceLoader_loadMesh(filename, mesh);
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

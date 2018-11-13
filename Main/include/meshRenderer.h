#ifndef MESHRENDERER_H
#define MESHRENDERER_H

#include <CoreEngine/engine3D_gameComponent.h>
#include <RenderingEngine/engine3D_mesh.h>
#include <RenderingEngine/engine3D_material.h>

typedef struct meshRenderer_t {
  engine3D_gameComponent_t baseComponent;
  engine3D_mesh_t *mesh;
  engine3D_material_t *material;
} meshRenderer_t;

meshRenderer_t *meshRenderer_init(meshRenderer_t *const meshRenderer, engine3D_mesh_t *mesh, engine3D_material_t *material);

#endif /* MESHRENDERER_H */

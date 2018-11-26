#ifndef MESHRENDERER_H
#define MESHRENDERER_H

#include <CoreEngine/engine3D_gameComponent.h>
#include <RenderingEngine/engine3D_mesh.h>
#include <RenderingEngine/engine3D_camera.h>
#include <RenderingEngine/engine3D_material.h>

// a component to render a mesh
typedef struct meshRenderer_t {
  engine3D_gameComponent_t baseComponent;
  engine3D_mesh_t *mesh;
  engine3D_material_t *material;
  engine3D_camera_t *camera;
} meshRenderer_t;

// create the component, needs the mesh to render, the material to render it with, and a camera to see it from
meshRenderer_t *meshRenderer_init(meshRenderer_t *const meshRenderer, engine3D_mesh_t *mesh, engine3D_material_t *material, engine3D_camera_t *const camera);

#endif /* MESHRENDERER_H */

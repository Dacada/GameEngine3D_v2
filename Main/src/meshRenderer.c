#include <meshRenderer.h>
#include <CoreEngine/engine3D_gameObject.h>
#include <RenderingEngine/engine3D_shader.h>
#include <RenderingEngine/engine3D_basicShader.h>
#include <RenderingEngine/engine3D_camera.h>
#include <Base/engine3D_transform.h>

static void render(engine3D_gameComponent_t *component) {
  meshRenderer_t *meshRenderer = (meshRenderer_t*)component;

  engine3D_shader_bind((engine3D_shader_t *)engine3D_basicShader_getInstance());

  engine3D_matrix4f_t transformation, projectedTransformation;
  engine3D_transform_getTransformation(component->gameObject->transform, &transformation);
  engine3D_camera_getProjectedTransformation(engine3D_camera_getInstance(), component->gameObject->transform, &projectedTransformation);
  engine3D_basicShader_updateUniforms(engine3D_basicShader_getInstance(), &transformation, &projectedTransformation, meshRenderer->material);

  engine3D_mesh_draw(meshRenderer->mesh);
}

meshRenderer_t *meshRenderer_init(meshRenderer_t *const meshRenderer, engine3D_mesh_t *mesh, engine3D_material_t *material) {
  engine3D_gameComponent_init((engine3D_gameComponent_t*)meshRenderer);
  meshRenderer->baseComponent.render = &render;
  meshRenderer->mesh = mesh;
  meshRenderer->material = material;
  return meshRenderer;
}

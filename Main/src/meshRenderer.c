#include <meshRenderer.h>
#include <CoreEngine/engine3D_gameObject.h>
#include <RenderingEngine/engine3D_shader.h>
#include <RenderingEngine/engine3D_basicShader.h>
#include <RenderingEngine/engine3D_camera.h>
#include <Base/engine3D_transform.h>

static void render(engine3D_gameComponent_t *const component, engine3D_shader_t *const shader) {
  meshRenderer_t *meshRenderer = (meshRenderer_t*)component;

  engine3D_shader_bind(shader);
  shader->updateUniforms(shader, component->gameObject->transform, meshRenderer->camera, meshRenderer->material);
  engine3D_mesh_draw(meshRenderer->mesh);
}

meshRenderer_t *meshRenderer_init(meshRenderer_t *const meshRenderer, engine3D_mesh_t *mesh, engine3D_material_t *material, engine3D_camera_t *const camera) {
  engine3D_gameComponent_init((engine3D_gameComponent_t*)meshRenderer);
  meshRenderer->baseComponent.render = &render;
  meshRenderer->mesh = mesh;
  meshRenderer->material = material;
  meshRenderer->camera = camera;
  return meshRenderer;
}

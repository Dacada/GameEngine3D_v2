#include <engine3D_gameObject.h>
#include <engine3D_gameComponent.h>
#include <Base/engine3D_growingArray.h>
#include <Base/engine3D_util.h>
#include <Base/engine3D_transform.h>

engine3D_gameObject_t *engine3D_gameObject_init(engine3D_gameObject_t *const gameObject) {
  gameObject->transform = engine3D_util_safeMalloc(sizeof(engine3D_transform_t));
  engine3D_transform_reset(gameObject->transform);
  
  gameObject->children = engine3D_util_safeMalloc(sizeof(engine3D_growingArray_t));
  engine3D_growingArray_init(gameObject->children, sizeof(engine3D_gameObject_t*), 4);

  gameObject->components = engine3D_util_safeMalloc(sizeof(engine3D_growingArray_t));
  engine3D_growingArray_init(gameObject->components, sizeof(engine3D_gameComponent_t*), 4);
  
  return gameObject;
}

void engine3D_gameObject_addChild(engine3D_gameObject_t *const gameObject, engine3D_gameObject_t *const child) {
  engine3D_gameObject_t **childPtr = engine3D_growingArray_add(gameObject->children);
  *childPtr = child;
}

void engine3D_gameObject_addComponent(engine3D_gameObject_t *const gameObject, engine3D_gameComponent_t *const component) {
  engine3D_gameComponent_t **componentPtr = engine3D_growingArray_add(gameObject->components);
  *componentPtr = component;
  component->gameObject = gameObject;
  component->init(component);
}

void engine3D_gameObject_input(engine3D_gameObject_t *const gameObject, const double delta) {
  for (size_t i = 0; i < engine3D_growingArray_length(gameObject->components); i++) {
    engine3D_gameComponent_t **component = engine3D_growingArray_getAt(gameObject->components, i);
    (*component)->input(*component, delta);
  }
  
  for (size_t i = 0; i < engine3D_growingArray_length(gameObject->children); i++) {
    engine3D_gameObject_t **child = engine3D_growingArray_getAt(gameObject->children, i);
    engine3D_gameObject_input(*child, delta);
  }
}

void engine3D_gameObject_update(engine3D_gameObject_t *const gameObject, const double delta) {
  for (size_t i = 0; i < engine3D_growingArray_length(gameObject->components); i++) {
    engine3D_gameComponent_t **component = engine3D_growingArray_getAt(gameObject->components, i);
    (*component)->update(*component, delta);
  }
  
  for (size_t i = 0; i < engine3D_growingArray_length(gameObject->children); i++) {
    engine3D_gameObject_t **child = engine3D_growingArray_getAt(gameObject->children, i);
    engine3D_gameObject_update(*child, delta);
  }
}

void engine3D_gameObject_render(const engine3D_gameObject_t *const gameObject, engine3D_shader_t *const shader) {
  for (size_t i = 0; i < engine3D_growingArray_length(gameObject->components); i++) {
    engine3D_gameComponent_t **component = engine3D_growingArray_getAt(gameObject->components, i);
    (*component)->render(*component, shader);
  }
  
  for (size_t i = 0; i < engine3D_growingArray_length(gameObject->children); i++) {
    engine3D_gameObject_t **child = engine3D_growingArray_getAt(gameObject->children, i);
    engine3D_gameObject_render(*child, shader);
  }
}

void engine3D_gameObject_cleanup(engine3D_gameObject_t *const gameObject) {
  for (size_t i = 0; i < engine3D_growingArray_length(gameObject->children); i++) {
    engine3D_gameObject_t **child = engine3D_growingArray_getAt(gameObject->children, i);
    engine3D_gameObject_cleanup(*child);
  }
  engine3D_growingArray_discard(gameObject->children);
  free(gameObject->children);
  gameObject->children = NULL;
  
  for (size_t i = 0; i < engine3D_growingArray_length(gameObject->components); i++) {
    engine3D_gameComponent_t **component = engine3D_growingArray_getAt(gameObject->components, i);
    (*component)->cleanup(*component);
  }
  engine3D_growingArray_discard(gameObject->components);
  free(gameObject->components);
  gameObject->components = NULL;

  free(gameObject->transform);
  gameObject->transform = NULL;
}

#ifndef ENGINE3D_GAMEOBJECT_H
#define ENGINE3D_GAMEOBJECT_H

#include "engine3D_gameComponent.h"
#include <Base/engine3D_growingArray.h>
#include <Base/engine3D_transform.h>

typedef struct engine3D_gameObject_t {
  engine3D_growingArray_t *children;
  engine3D_growingArray_t *components;
  engine3D_transform_t *transform;
} engine3D_gameObject_t;

engine3D_gameObject_t *engine3D_gameObject_init(engine3D_gameObject_t *const gameObject);

void engine3D_gameObject_addChild(engine3D_gameObject_t *const gameObject, engine3D_gameObject_t *const child);

void engine3D_gameObject_addComponent(engine3D_gameObject_t *const gameObject, engine3D_gameComponent_t *const component);

void engine3D_gameObject_input(engine3D_gameObject_t *const gameObject);

void engine3D_gameObject_update(engine3D_gameObject_t *const gameObject);

void engine3D_gameObject_render(engine3D_gameObject_t *const gameObject);

void engine3D_gameObject_cleanup(engine3D_gameObject_t *const gameObject);

#endif /* ENGINE3D_GAMECOMPONENT_H */

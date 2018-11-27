#ifndef ENGINE3D_GAMEOBJECT_H
#define ENGINE3D_GAMEOBJECT_H

#include "engine3D_gameComponent.h"
#include <RenderingEngine/engine3D_shader.h>
#include <Base/engine3D_growingArray.h>
#include <Base/engine3D_transform.h>

// a game object in the game object hierarchy
typedef struct engine3D_gameObject_t {
  engine3D_growingArray_t *children; // each of the children of the game object, a growing array of game objects
  engine3D_growingArray_t *components; // each of the components of this object, a growing array of object components
  engine3D_transform_t *transform; // the transform of this object
} engine3D_gameObject_t;

// initialize the object and allocate space for the growing arrays and the transform
engine3D_gameObject_t *engine3D_gameObject_init(engine3D_gameObject_t *const gameObject);

// add a child to the object
void engine3D_gameObject_addChild(engine3D_gameObject_t *const gameObject, engine3D_gameObject_t *const child);

// add a component to the object
void engine3D_gameObject_addComponent(engine3D_gameObject_t *const gameObject, engine3D_gameComponent_t *const component);

// process input for the object: process input for all its components and all its children objects
void engine3D_gameObject_input(engine3D_gameObject_t *const gameObject, const double delta);

// process updates for the object: process updates for its components and all its children objects
void engine3D_gameObject_update(engine3D_gameObject_t *const gameObject, const double delta);

// render this object: render its components and all its children objects
void engine3D_gameObject_render(const engine3D_gameObject_t *const gameObject,engine3D_shader_t *const shader);

// deallocate space used by this object, also recursively called on all its components and children
void engine3D_gameObject_cleanup(engine3D_gameObject_t *const gameObject);

#endif /* ENGINE3D_GAMECOMPONENT_H */

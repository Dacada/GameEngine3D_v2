#ifndef ENGINE3D_GAMECOMPONENT_H
#define ENGINE3D_GAMECOMPONENT_H

#include <RenderingEngine/engine3D_shader.h>

struct engine3D_gameObject_t;

// Component of a game object
typedef struct engine3D_gameComponent_t {
  void(*init)(struct engine3D_gameComponent_t *const); // initialize the component when adding it to the game object
  void(*input)(struct engine3D_gameComponent_t *const, const double); // process inputs
  void(*update)(struct engine3D_gameComponent_t *const, const double); // update variables
  void(*render)(struct engine3D_gameComponent_t *const, engine3D_shader_t *const shader); // render something, using th given shader
  void(*cleanup)(struct engine3D_gameComponent_t*); // cleanup on exit
  struct engine3D_gameObject_t *gameObject; // game object this component is attached to
} engine3D_gameComponent_t;

// construct a game component, giving values to its callbacks, which call empty functions
engine3D_gameComponent_t *engine3D_gameComponent_init(engine3D_gameComponent_t *const gameComponent);

#endif /* ENGINE3D_GAMECOMPONENT_H */

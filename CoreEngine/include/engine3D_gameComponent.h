#ifndef ENGINE3D_GAMECOMPONENT_H
#define ENGINE3D_GAMECOMPONENT_H

struct engine3D_gameObject_t;

typedef struct engine3D_gameComponent_t {
  void(*init)(struct engine3D_gameComponent_t*);
  void(*input)(struct engine3D_gameComponent_t*);
  void(*update)(struct engine3D_gameComponent_t*);
  void(*render)(struct engine3D_gameComponent_t*);
  void(*cleanup)(struct engine3D_gameComponent_t*);
  struct engine3D_gameObject_t *gameObject;
} engine3D_gameComponent_t;

engine3D_gameComponent_t *engine3D_gameComponent_init(engine3D_gameComponent_t *const gameComponent);

#endif /* ENGINE3D_GAMECOMPONENT_H */

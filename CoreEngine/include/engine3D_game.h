#ifndef ENGINE3D_GAME_H
#define ENGINE3D_GAME_H

#include "engine3D_gameObject.h"

// state and methods of a game to be overridden by an actual implementation, ran by an engine
typedef struct engine3D_game_t {
  void(*init)(struct engine3D_game_t *const); // init method to initialize the game
  void(*input)(struct engine3D_game_t *const, const double delta); // input method to process input
  void(*update)(struct engine3D_game_t *const, const double delta); // update method to update internal state
  void(*cleanup)(struct engine3D_game_t *const); // cleanup method to deallocate and clean elements
  engine3D_gameObject_t *root; // root game object of the object hierarchy
} engine3D_game_t;

// basic constructor, gives values to each of the function callbacks
engine3D_game_t *engine3D_game_init(engine3D_game_t *const game);

#endif /* ENGINE3D_GAME_H */

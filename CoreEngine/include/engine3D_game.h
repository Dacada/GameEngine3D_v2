#ifndef ENGINE3D_GAME_H
#define ENGINE3D_GAME_H

typedef struct engine3D_game_t {
  void(*init)(struct engine3D_game_t*);
  void(*input)(struct engine3D_game_t*);
  void(*update)(struct engine3D_game_t*);
  void(*render)(struct engine3D_game_t*);
  void(*cleanup)(struct engine3D_game_t*);
} engine3D_game_t;

#endif /* ENGINE3D_GAME_H */

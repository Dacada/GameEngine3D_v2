#ifndef ENGINE3D_MAIN_H
#define ENGINE3D_MAIN_H

#include <RenderingEngine/engine3D_window.h>

typedef struct engine3D_game_t {
  void(*init)(void);
  void(*input)(void);
  void(*update)(void);
  void(*render)(void);
  void(*cleanup)(void);
} engine3D_game_t;

typedef struct engine3D_core_t {
  int windowWidth;
  int windowHeight;
  int fps;
  bool isRunning;
  double frameTime;
  engine3D_window_t *window;
  engine3D_game_t *game;
} engine3D_core_t;

void engine3D_core_init(engine3D_core_t *engine, int width, int height, double frameRate, engine3D_game_t *game);

void engine3D_core_createWindow(engine3D_core_t *engine, const char *const title);

void engine3D_core_start(engine3D_core_t *engine);

void engine3D_core_stop(engine3D_core_t *engine);

#endif /* ENGINE3D_MAIN_H */

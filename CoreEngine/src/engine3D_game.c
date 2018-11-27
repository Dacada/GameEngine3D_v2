#include <engine3D_game.h>
#include <Base/engine3D_util.h>

void init(engine3D_game_t *const game) {
  game->root = engine3D_util_safeMalloc(sizeof(engine3D_gameObject_t));
  engine3D_gameObject_init(game->root);
}
void input(engine3D_game_t *const game, const double delta) {
  engine3D_gameObject_input(game->root, delta);
}
void update(engine3D_game_t *const game, const double delta) {
  engine3D_gameObject_update(game->root, delta);
}
void cleanup(engine3D_game_t *const game) {
  engine3D_gameObject_cleanup(game->root);
  free(game->root);
}

engine3D_game_t *engine3D_game_init(engine3D_game_t *const game) {
  game->init = &init;
  game->input = &input;
  game->update = &update;
  game->cleanup = &cleanup;
  return game;
}

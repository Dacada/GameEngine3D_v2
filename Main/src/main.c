#include <gameImplementation.h>

engine3D_core_t engine;
myGameImplementation game;

int main(void) {
  makeMyGameImplementation(&game);
  game.engine = &engine;
  game.width = 800;
  game.height = 600;

	engine3D_core_init(&engine, game.width, game.height, 60, (engine3D_game_t*)&game);
	engine3D_core_createWindow(&engine, "3D Game Engine");
	engine3D_core_start(&engine);

	return EXIT_SUCCESS;
}

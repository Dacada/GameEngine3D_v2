#include <Base/engine3D_util.h>
#include <Base/engine3D_transform.h>
#include <Base/engine3D_time.h>
#include <RenderingEngine/engine3D_window.h>
#include <engine3D_input.h>
#include <engine3D_core.h>
#include <stdio.h>
#include <stdbool.h>

static void cleanup(engine3D_core_t *engine) {
	engine3D_window_destroy(engine->window);
	free(engine->renderer);
	engine->game->cleanup(engine->game);
}

static void run(engine3D_core_t *engine) {
	double frameCounter = 0;

	double lastFrameTime = engine3D_timer_getTime();
	double unprocessedTime = 0;

	while (engine->isRunning) {
		bool doRender = false;

		double currentFrameTime = engine3D_timer_getTime();
		double lastFrameElapsedTime = currentFrameTime - lastFrameTime;
		lastFrameTime = currentFrameTime;

		unprocessedTime += lastFrameElapsedTime;
		frameCounter += lastFrameElapsedTime;

		while (unprocessedTime > engine->frameTime)
		{
			doRender = true;

			unprocessedTime -= engine->frameTime;

			if (engine3D_window_closeRequested(engine->window)) {
				engine3D_core_stop(engine);
			}

			double delta = engine->frameTime;

			engine->game->input(engine->game, delta);
			engine3D_input_update();

			engine->game->update(engine->game, delta);

			if (frameCounter >= 1) {
				engine3D_util_debugPrintf("%d", engine->fps);

				engine->fps = 0;
				frameCounter = 0;
			}
		}

		if (doRender) {
		  engine3D_renderer_render(engine->renderer, engine->game->root);
		  engine3D_window_update(engine->window);
		  engine->fps++;
		} else {
			engine3D_time_sleep(0.001);
		}
	}

	cleanup(engine);
}

void engine3D_core_init(engine3D_core_t *engine, int width, int height, double frameRate, engine3D_game_t *g) {
	engine3D_timer_init();
	engine->isRunning = false;
	engine->windowWidth = width;
	engine->windowHeight = height;
	engine->frameTime = 1.0 / frameRate;
	engine->game = g;
}

void engine3D_core_createWindow(engine3D_core_t *engine, const char *const title) {
  engine3D_window_t *window = engine3D_window_create(engine->windowWidth, engine->windowHeight, title);
  engine->window = window;
  engine3D_input_init(window);
  engine->renderer = engine3D_renderer_init(engine3D_util_safeMalloc(sizeof(engine3D_renderer_t)));
  engine3D_util_debugPrint(engine3D_renderer_getOpenGLVersion());
}

void engine3D_core_start(engine3D_core_t *engine) {
	if (engine->isRunning) {
		engine3D_util_bail("Attempt to start already running engine. Aborting.");
	}
	engine->game->init(engine->game);
	engine->isRunning = true;
	run(engine);
}

void engine3D_core_stop(engine3D_core_t *engine) {
	engine->isRunning = false;
}

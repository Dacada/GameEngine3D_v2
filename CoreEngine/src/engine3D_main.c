#include <Base/engine3D_util.h>
#include <Base/engine3D_transform.h>
#include <Base/engine3D_time.h>
#include <RenderingEngine/engine3D_window.h>
#include <RenderingEngine/engine3D_renderUtil.h>
#include <engine3D_input.h>
#include <engine3D_main.h>
#include <stdio.h>
#include <stdbool.h>

const int engine3D_width = 800;
const int engine3D_height = 600;
const char *const engine3D_title = "3D Engine";
const double engine3D_frameCap = 5000.0;

int engine3D_fps = 0;

static bool isRunning = false;

static game_callback_t game_init;
static game_callback_t game_input;
static game_callback_t game_update;
static game_callback_t game_render;
static game_callback_t game_cleanup;

static void cleanup(void) {
	engine3D_window_destroy();
  game_cleanup();
}

static void render(void) {
	engine3D_renderUtil_clearScreen();
	game_render();
	engine3D_window_update();
}

static void run(void) {
	isRunning = true;

	double frameCounter = 0;

	const double frameTime = 1.0 / engine3D_frameCap;

	double lastFrameTime = engine3D_timer_getTime();
	double unprocessedTime = 0;

	while (isRunning) {
		bool doRender = false;

		double currentFrameTime = engine3D_timer_getTime();
		double lastFrameElapsedTime = currentFrameTime - lastFrameTime;
		lastFrameTime = currentFrameTime;

		unprocessedTime += lastFrameElapsedTime / engine3D_timer_second;
		frameCounter += lastFrameElapsedTime;

		while (unprocessedTime > frameTime)
		{
			doRender = true;

			unprocessedTime -= frameTime;

			if (engine3D_window_closeRequested()) {
				engine3D_stop();
			}

			engine3D_time_setDelta(frameTime);

			game_input();
			engine3D_input_update();

			game_update();

			if (frameCounter >= engine3D_timer_second) {
				engine3D_util_debugPrintf("%d", engine3D_fps);

				engine3D_fps = 0;
				frameCounter = 0;
			}
		}

		if (doRender) {
			render();
			engine3D_fps++;
		} else {
			engine3D_time_sleep(0.001 * engine3D_timer_second);
		}
	}

	cleanup();
}

void engine3D_init(void) {
	engine3D_timer_init();
	engine3D_window_t *window = engine3D_window_create(engine3D_width, engine3D_height, engine3D_title);
	engine3D_input_init(window);
	engine3D_renderUtil_initGraphics();
	puts(engine3D_renderUtil_getOpenGLVersion());
	game_init();
}

void engine3D_start(void) {
	if (isRunning) {
		return;
	}
	run();
}

void engine3D_stop(void) {
	isRunning = false;
}

void engine3D_setGame_init(const game_callback_t fun) {
	game_init = fun;
}

void engine3D_setGame_input(const game_callback_t fun) {
	game_input = fun;
}

void engine3D_setGame_update(const game_callback_t fun) {
	game_update = fun;
}

void engine3D_setGame_render(const game_callback_t fun) {
	game_render = fun;
}

void engine3D_setGame_cleanup(const game_callback_t fun) {
	game_cleanup = fun;
}

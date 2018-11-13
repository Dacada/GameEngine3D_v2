#include <gameImplementation.h>
#include <Base/engine3D_time.h>
#include <Base/engine3D_transform.h>
#include <Base/engine3D_util.h>
#include <RenderingEngine/engine3D_vertex.h>
#include <RenderingEngine/engine3D_mesh.h>
#include <RenderingEngine/engine3D_shader.h>
#include <RenderingEngine/engine3D_phongShader.h>
#include <RenderingEngine/engine3D_camera.h>
#include <RenderingEngine/engine3D_texture.h>
#include <meshRenderer.h>
#include <RenderingEngine/engine3D_renderUtil.h>
#include <CoreEngine/engine3D_core.h>
#include <CoreEngine/engine3D_input.h>
#include <CoreEngine/engine3D_gameObject.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

static engine3D_transform_t transform;
static engine3D_vector3f_t color;
static engine3D_texture_t texture;
static engine3D_material_t material;
static engine3D_mesh_t mesh;

static engine3D_gameObject_t root;
static meshRenderer_t meshRenderer;

static void init(engine3D_game_t *g) {
  myGameImplementation *game = (myGameImplementation*)g;
	game->root = &root;
	engine3D_gameObject_init(&root);
	
	engine3D_util_resourcesPath = "Main/res/";

	color.x = 1; color.y = 1; color.z = 1;
	texture = engine3D_texture_loadFromFile("test.png");
        material.texture = &texture;
	material.color = color;

	engine3D_mesh_init(&mesh);
	float fieldDepth = 10;
	float fieldWidth = 10;
	engine3D_vertex_t vertices[] = { { {-fieldWidth,     0, -fieldDepth    },{0, 0},{0, 0, 0} },
				         { {-fieldWidth,     0,  fieldDepth * 3},{0, 1},{0, 0, 0} },
				         { { fieldWidth * 3, 0, -fieldDepth    },{1, 0},{0, 0, 0} },
				         { { fieldWidth * 3, 0, fieldDepth * 3 },{1, 1},{0, 0, 0} } };
	unsigned int indices[] = { 0,1,2, 2,1,3 };
	engine3D_mesh_addVertices(&mesh, vertices, 4, indices, 6, true);
	
	meshRenderer_init(&meshRenderer, &mesh, &material);
	engine3D_gameObject_addComponent(&root, (engine3D_gameComponent_t*)&meshRenderer);

	root.transform = &transform;
	engine3D_transform_reset(root.transform);
	root.transform->translation.z = 5;

	engine3D_transform_zNear = 0.1f;
	engine3D_transform_zFar = 1000.0f;
	engine3D_transform_width = (float)game->width;
	engine3D_transform_height = (float)game->height;
	engine3D_transform_fov = 70.0f;
}

static void generalInput(myGameImplementation *game, float delta) {
  UNUSED(delta);

	if (engine3D_input_getKey(ENGINE3D_KEY_ESCAPE)) {
		engine3D_core_stop(game->engine);
	}
}

static void cameraInput(myGameImplementation *game, float delta) {
  UNUSED(game);
	float sensitivity = 0.5f;
	float movAmt = delta * 10;

	static bool movingCamera = false;
	static engine3D_vector2f_t centerPosition;
	if (engine3D_input_getMouseDown(ENGINE3D_MOUSE_BUTTON_LEFT)) {
		engine3D_input_setCursor(ENGINE3D_CURSOR_DISABLED);
		engine3D_input_getMousePosition(&centerPosition);
		movingCamera = true;
	}

	if (engine3D_input_getMouseUp(ENGINE3D_MOUSE_BUTTON_LEFT)) {
		engine3D_input_setCursor(ENGINE3D_CURSOR_ENABLED);
		movingCamera = false;
	}

	if (engine3D_input_getKey(ENGINE3D_KEY_W)) {
		engine3D_camera_move(engine3D_camera_getInstance(), engine3D_camera_getInstance()->forward, movAmt);
	}
	if (engine3D_input_getKey(ENGINE3D_KEY_S)) {
		engine3D_camera_move(engine3D_camera_getInstance(), engine3D_camera_getInstance()->forward, -movAmt);
	}
	if (engine3D_input_getKey(ENGINE3D_KEY_A)) {
		engine3D_vector3f_t vec;
		engine3D_camera_left(engine3D_camera_getInstance(), &vec);
		engine3D_camera_move(engine3D_camera_getInstance(), vec, movAmt);
	}
	if (engine3D_input_getKey(ENGINE3D_KEY_D)) {
		engine3D_vector3f_t vec;
		engine3D_camera_right(engine3D_camera_getInstance(), &vec);
		engine3D_camera_move(engine3D_camera_getInstance(), vec, movAmt);
	}

	if (movingCamera) {
		engine3D_vector2f_t pos, deltaPos;
		engine3D_input_getMousePosition(&pos);
		deltaPos = engine3D_vector2f_sub(pos, centerPosition);

		if (deltaPos.x != 0)
		{
			engine3D_camera_rotateY(engine3D_camera_getInstance(), deltaPos.x * sensitivity * delta);
		}

		if (deltaPos.y != 0)
		{
			engine3D_camera_rotateX(engine3D_camera_getInstance(), deltaPos.y * sensitivity * delta);
		}
	}
}

static void input(engine3D_game_t *g) {
  myGameImplementation *game = (myGameImplementation*)g;
	float t = (float)engine3D_time_getDelta();

	generalInput(game, t);
	cameraInput(game, t);

	engine3D_gameObject_input(game->root);
}

static void update(engine3D_game_t *g) {
  myGameImplementation *game = (myGameImplementation*)g;

  engine3D_gameObject_update(game->root);

	transform.translation.x = 0;
	transform.translation.y = -1;
	transform.translation.z = 5;
}

static void render(engine3D_game_t *g) {
  myGameImplementation *game = (myGameImplementation*)g;
  engine3D_gameObject_render(game->root);
}

static void cleanup(engine3D_game_t *g) {
  myGameImplementation *game = (myGameImplementation*)g;
  engine3D_gameObject_cleanup(game->root);
}

void makeMyGameImplementation(myGameImplementation *game) {
  UNUSED(game);
	game->game.init = &init;
	game->game.input = &input;
	game->game.update = &update;
	game->game.render = &render;
	game->game.cleanup = &cleanup;
}

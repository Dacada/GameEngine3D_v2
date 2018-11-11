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
#include <RenderingEngine/engine3D_renderUtil.h>
#include <CoreEngine/engine3D_core.h>
#include <CoreEngine/engine3D_input.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

static void init(engine3D_game_t *g) {
  myGameImplementation *game = (myGameImplementation*)g;
	engine3D_util_resourcesPath = "Main/res/";

	engine3D_phongShader_init(&game->shader);
	engine3D_transform_reset(&game->transform);
	game->transform.translation.z = 5;

	game->color.x = 1; game->color.y = 1; game->color.z = 1;
	game->texture = engine3D_texture_loadFromFile("test.png");
	game->material.texture = &game->texture;
	game->material.color = game->color;
	game->material.specularIntensity = 1;
	game->material.specularPower = 8;

	//engine3D_mesh_initFromFile("tetrahedron.obj", &game->mesh);
	engine3D_mesh_init(&game->mesh);
	float fieldDepth = 10;
	float fieldWidth = 10;
	engine3D_vertex_t vertices[] = { { {-fieldWidth,     0, -fieldDepth    },{0, 0},{0, 0, 0} },
				         { {-fieldWidth,     0,  fieldDepth * 3},{0, 1},{0, 0, 0} },
				         { { fieldWidth * 3, 0, -fieldDepth    },{1, 0},{0, 0, 0} },
				         { { fieldWidth * 3, 0, fieldDepth * 3 },{1, 1},{0, 0, 0} } };
	unsigned int indices[] = { 0,1,2, 2,1,3 };
	engine3D_mesh_addVertices(&game->mesh, vertices, 4, indices, 6, true);

	engine3D_transform_zNear = 0.1f;
	engine3D_transform_zFar = 1000.0f;
	engine3D_transform_width = (float)game->width;
	engine3D_transform_height = (float)game->height;
	engine3D_transform_fov = 70.0f;
	engine3D_camera_init(&game->camera);

	engine3D_phongShader_ambientLight.x = 0.1f;
	engine3D_phongShader_ambientLight.y = 0.1f;
	engine3D_phongShader_ambientLight.z = 0.1f;

	engine3D_phongShader_directionalLight.base.color.x = 0; // 1;
	engine3D_phongShader_directionalLight.base.color.y = 0; // 1;
	engine3D_phongShader_directionalLight.base.color.z = 0; // 1;
	engine3D_phongShader_directionalLight.base.intensity = 0; //0.8f;
	engine3D_phongShader_directionalLight.direction.x = 1;
	engine3D_phongShader_directionalLight.direction.y = 1;
	engine3D_phongShader_directionalLight.direction.z = 1;
	engine3D_vector3f_normalize(&engine3D_phongShader_directionalLight.direction);

	engine3D_phongShader_pointLights[0].base.color.x = 1;
	engine3D_phongShader_pointLights[0].base.color.y = 0.5f;
	engine3D_phongShader_pointLights[0].base.color.z = 0;
	engine3D_phongShader_pointLights[0].base.intensity = 0.8f;
	engine3D_phongShader_pointLights[0].atten.constant = 0;
	engine3D_phongShader_pointLights[0].atten.linear = 0;
	engine3D_phongShader_pointLights[0].atten.exponent = 1;
	engine3D_phongShader_pointLights[0].position.x = 3;
	engine3D_phongShader_pointLights[0].position.x = 0;
	engine3D_phongShader_pointLights[0].position.x = 8;
	engine3D_phongShader_pointLights[0].range = 6;

	engine3D_phongShader_pointLights[1].base.color.x = 0;
	engine3D_phongShader_pointLights[1].base.color.y = 0.5f;
	engine3D_phongShader_pointLights[1].base.color.z = 1;
	engine3D_phongShader_pointLights[1].base.intensity = 0.8f;
	engine3D_phongShader_pointLights[1].atten.constant = 0;
	engine3D_phongShader_pointLights[1].atten.linear = 0;
	engine3D_phongShader_pointLights[1].atten.exponent = 1;
	engine3D_phongShader_pointLights[1].position.x = 7;
	engine3D_phongShader_pointLights[1].position.x = 0;
	engine3D_phongShader_pointLights[1].position.x = 8;
	engine3D_phongShader_pointLights[1].range = 6;

	engine3D_phongShader_spotLights[0].pointLight.base.color.x = 0;
	engine3D_phongShader_spotLights[0].pointLight.base.color.y = 1;
	engine3D_phongShader_spotLights[0].pointLight.base.color.z = 1;
	engine3D_phongShader_spotLights[0].pointLight.base.intensity = 0.8f;
	engine3D_phongShader_spotLights[0].pointLight.atten.constant = 0;
	engine3D_phongShader_spotLights[0].pointLight.atten.linear = 0;
	engine3D_phongShader_spotLights[0].pointLight.atten.exponent = 0.1f;
	engine3D_phongShader_spotLights[0].pointLight.position.x = game->camera.pos.x;
	engine3D_phongShader_spotLights[0].pointLight.position.y = game->camera.pos.y;
	engine3D_phongShader_spotLights[0].pointLight.position.z = game->camera.pos.z;
	engine3D_phongShader_spotLights[0].pointLight.range = 30;
	engine3D_phongShader_spotLights[0].direction.x = game->camera.forward.x;
	engine3D_phongShader_spotLights[0].direction.y = game->camera.forward.y;
	engine3D_phongShader_spotLights[0].direction.z = game->camera.forward.z;
	engine3D_phongShader_spotLights[0].cutoff = 0.7f;

	//engine3D_phongShader_numberOfPointLights = 2;
	engine3D_phongShader_numberOfSpotLights = 1;
}

static void generalInput(myGameImplementation *game, float delta) {
  UNUSED(delta);

	if (engine3D_input_getKey(ENGINE3D_KEY_ESCAPE)) {
		engine3D_core_stop(game->engine);
	}
}

static void cameraInput(myGameImplementation *game, float delta) {
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
		engine3D_camera_move(&game->camera, game->camera.forward, movAmt);
	}
	if (engine3D_input_getKey(ENGINE3D_KEY_S)) {
		engine3D_camera_move(&game->camera, game->camera.forward, -movAmt);
	}
	if (engine3D_input_getKey(ENGINE3D_KEY_A)) {
		engine3D_vector3f_t vec;
		engine3D_camera_left(&game->camera, &vec);
		engine3D_camera_move(&game->camera, vec, movAmt);
	}
	if (engine3D_input_getKey(ENGINE3D_KEY_D)) {
		engine3D_vector3f_t vec;
		engine3D_camera_right(&game->camera, &vec);
		engine3D_camera_move(&game->camera, vec, movAmt);
	}

	if (movingCamera) {
		engine3D_vector2f_t pos, deltaPos;
		engine3D_input_getMousePosition(&pos);
		deltaPos = engine3D_vector2f_sub(pos, centerPosition);

		if (deltaPos.x != 0)
		{
			engine3D_camera_rotateY(&game->camera, deltaPos.x * sensitivity * delta);
		}

		if (deltaPos.y != 0)
		{
			engine3D_camera_rotateX(&game->camera, deltaPos.y * sensitivity * delta);
		}
	}
}

static void input(engine3D_game_t *g) {
  myGameImplementation *game = (myGameImplementation*)g;
	float t = (float)engine3D_time_getDelta();

	generalInput(game, t);
	cameraInput(game, t);
}

static void update(engine3D_game_t *g) {
  myGameImplementation *game = (myGameImplementation*)g;
	static float tmp = 0.0f;
	tmp += (float)engine3D_time_getDelta();

	game->transform.translation.x = 0;
	game->transform.translation.y = -1;
	game->transform.translation.z = 5;
	//transform.rotation.x = 0;
	//transform.rotation.y = sinTmp * 180;
	//transform.rotation.z = 0;
	//transform.scale.x = sinTmp;
	//transform.scale.y = sinTmp;
	//transform.scale.z = sinTmp;

	engine3D_phongShader_pointLights[0].position.z = 8 * sinf(tmp) + 1.0f / 2.0f + 10;
	engine3D_phongShader_pointLights[1].position.z = 8 * cosf(tmp) + 1.0f / 2.0f + 10;

	engine3D_phongShader_spotLights[0].pointLight.position.x = game->camera.pos.x;
	engine3D_phongShader_spotLights[0].pointLight.position.y = game->camera.pos.y;
	engine3D_phongShader_spotLights[0].pointLight.position.z = game->camera.pos.z;
	engine3D_phongShader_spotLights[0].direction.x = game->camera.forward.x;
	engine3D_phongShader_spotLights[0].direction.y = game->camera.forward.y;
	engine3D_phongShader_spotLights[0].direction.z = game->camera.forward.z;
}

static void render(engine3D_game_t *g) {
  myGameImplementation *game = (myGameImplementation*)g;
	engine3D_renderUtils_setClearColor(engine3D_vector3f_abs(engine3D_vector3f_divf(game->camera.pos, 2048)));

	engine3D_shader_bind((engine3D_shader_t *)&game->shader);

	engine3D_matrix4f_t transformation, projectedTransformation;
	engine3D_transform_getTransformation(&game->transform, &transformation);
	engine3D_camera_getProjectedTransformation(&game->camera, &game->transform, &projectedTransformation);
	engine3D_phongShader_updateUniforms(&game->shader, &transformation, &projectedTransformation, &game->material, game->camera.pos);

	engine3D_mesh_draw(&game->mesh);
}

static void cleanup(engine3D_game_t *g) {
  myGameImplementation *game = (myGameImplementation*)g;
	engine3D_phongShader_destroy(&game->shader);
}

void makeMyGameImplementation(myGameImplementation *game) {
	game->game.init = &init;
	game->game.input = &input;
	game->game.update = &update;
	game->game.render = &render;
	game->game.cleanup = &cleanup;
}

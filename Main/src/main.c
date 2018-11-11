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

static engine3D_core_t engine;

static engine3D_mesh_t mesh;
static engine3D_phongShader_t shader;
static engine3D_transform_t transform;
static engine3D_material_t material;
static engine3D_camera_t camera;

static engine3D_texture_t texture;
static engine3D_vector3f_t color;

static const int width = 800;
static const int height = 600;

static void init(void) {
	engine3D_util_resourcesPath = "Main/res/";

	engine3D_phongShader_init(&shader);
	engine3D_transform_reset(&transform);
	transform.translation.z = 5;

	color.x = 1; color.y = 1; color.z = 1;
	texture = engine3D_texture_loadFromFile("test.png");
	material.texture = &texture;
	material.color = color;
	material.specularIntensity = 1;
	material.specularPower = 8;

	//engine3D_mesh_initFromFile("tetrahedron.obj", &mesh);
	engine3D_mesh_init(&mesh);
	float fieldDepth = 10;
	float fieldWidth = 10;
	engine3D_vertex_t vertices[] = { { {-fieldWidth,     0, -fieldDepth    },{0, 0},{0, 0, 0} },
									                 { {-fieldWidth,     0,  fieldDepth * 3},{0, 1},{0, 0, 0} },
									                 { { fieldWidth * 3, 0, -fieldDepth    },{1, 0},{0, 0, 0} },
									                 { { fieldWidth * 3, 0, fieldDepth * 3 },{1, 1},{0, 0, 0} } };
	unsigned int indices[] = { 0,1,2, 2,1,3 };
	engine3D_mesh_addVertices(&mesh, vertices, 4, indices, 6, true);

	engine3D_transform_zNear = 0.1f;
	engine3D_transform_zFar = 1000.0f;
	engine3D_transform_width = (float)width;
	engine3D_transform_height = (float)height;
	engine3D_transform_fov = 70.0f;
	engine3D_camera_init(&camera);

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
	engine3D_phongShader_spotLights[0].pointLight.position.x = camera.pos.x;
	engine3D_phongShader_spotLights[0].pointLight.position.y = camera.pos.y;
	engine3D_phongShader_spotLights[0].pointLight.position.z = camera.pos.z;
	engine3D_phongShader_spotLights[0].pointLight.range = 30;
	engine3D_phongShader_spotLights[0].direction.x = camera.forward.x;
	engine3D_phongShader_spotLights[0].direction.y = camera.forward.y;
	engine3D_phongShader_spotLights[0].direction.z = camera.forward.z;
	engine3D_phongShader_spotLights[0].cutoff = 0.7f;

	//engine3D_phongShader_numberOfPointLights = 2;
	engine3D_phongShader_numberOfSpotLights = 1;
}

static void generalInput(float delta) {
	(void)delta;

	if (engine3D_input_getKey(ENGINE3D_KEY_ESCAPE)) {
		engine3D_core_stop(&engine);
	}
}

static void cameraInput(float delta) {
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
		engine3D_camera_move(&camera, camera.forward, movAmt);
	}
	if (engine3D_input_getKey(ENGINE3D_KEY_S)) {
		engine3D_camera_move(&camera, camera.forward, -movAmt);
	}
	if (engine3D_input_getKey(ENGINE3D_KEY_A)) {
		engine3D_vector3f_t vec;
		engine3D_camera_left(&camera, &vec);
		engine3D_camera_move(&camera, vec, movAmt);
	}
	if (engine3D_input_getKey(ENGINE3D_KEY_D)) {
		engine3D_vector3f_t vec;
		engine3D_camera_right(&camera, &vec);
		engine3D_camera_move(&camera, vec, movAmt);
	}

	if (movingCamera) {
		engine3D_vector2f_t pos, deltaPos;
		engine3D_input_getMousePosition(&pos);
		deltaPos = engine3D_vector2f_sub(pos, centerPosition);

		if (deltaPos.x != 0)
		{
			engine3D_camera_rotateY(&camera, deltaPos.x * sensitivity * delta);
		}

		if (deltaPos.y != 0)
		{
			engine3D_camera_rotateX(&camera, deltaPos.y * sensitivity * delta);
		}
	}
}

static void input(void) {

	float t = (float)engine3D_time_getDelta();

	generalInput(t);
	cameraInput(t);
}

static void update(void) {
	static float tmp = 0.0f;
	tmp += (float)engine3D_time_getDelta();

	transform.translation.x = 0;
	transform.translation.y = -1;
	transform.translation.z = 5;
	//transform.rotation.x = 0;
	//transform.rotation.y = sinTmp * 180;
	//transform.rotation.z = 0;
	//transform.scale.x = sinTmp;
	//transform.scale.y = sinTmp;
	//transform.scale.z = sinTmp;

	engine3D_phongShader_pointLights[0].position.z = 8 * sinf(tmp) + 1.0f / 2.0f + 10;
	engine3D_phongShader_pointLights[1].position.z = 8 * cosf(tmp) + 1.0f / 2.0f + 10;

	engine3D_phongShader_spotLights[0].pointLight.position.x = camera.pos.x;
	engine3D_phongShader_spotLights[0].pointLight.position.y = camera.pos.y;
	engine3D_phongShader_spotLights[0].pointLight.position.z = camera.pos.z;
	engine3D_phongShader_spotLights[0].direction.x = camera.forward.x;
	engine3D_phongShader_spotLights[0].direction.y = camera.forward.y;
	engine3D_phongShader_spotLights[0].direction.z = camera.forward.z;
}

static void render(void) {
	engine3D_renderUtils_setClearColor(engine3D_vector3f_abs(engine3D_vector3f_divf(camera.pos, 2048)));

	engine3D_shader_bind((engine3D_shader_t *)&shader);

	engine3D_matrix4f_t transformation, projectedTransformation;
	engine3D_transform_getTransformation(&transform, &transformation);
	engine3D_camera_getProjectedTransformation(&camera, &transform, &projectedTransformation);
	engine3D_phongShader_updateUniforms(&shader, &transformation, &projectedTransformation, &material, camera.pos);

	engine3D_mesh_draw(&mesh);
}

static void cleanup(void) {
	engine3D_phongShader_destroy(&shader);
}

typedef struct myGameImplementation {
	engine3D_game_t game;
} myGameImplementation;

int main(void) {
	myGameImplementation game;

	game.game.init = &init;
	game.game.input = &input;
	game.game.update = &update;
	game.game.render = &render;
	game.game.cleanup = &cleanup;

	engine3D_core_init(&engine, width, height, 60, (engine3D_game_t*)&game);
	engine3D_core_createWindow(&engine, "3D Game Engine");
	engine3D_core_start(&engine);

	return EXIT_SUCCESS;
}

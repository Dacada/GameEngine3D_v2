#include <engine3D_camera.h>

#include <engine3D_vector.h>

#include <string.h>

static const engine3D_vector3f_t yAxis = { 0, 1, 0 };

void engine3D_camera_init(engine3D_camera_t *const camera) {
	camera->pos.x = 0;
	camera->pos.y = 0;
	camera->pos.z = 0;
	camera->forward.x = 0;
	camera->forward.y = 0;
	camera->forward.z = 1;
	camera->up.x = 0;
	camera->up.y = 2;
	camera->up.z = 0;
	engine3D_camera_normalize(camera);
}

void engine3D_camera_normalize(engine3D_camera_t *const camera) {
	engine3D_vector3f_normalize(&camera->forward);
	engine3D_vector3f_normalize(&camera->up);
}

void engine3D_camera_move(engine3D_camera_t *const camera, const engine3D_vector3f_t dir, const float amnt) {
	camera->pos = engine3D_vector3f_add(camera->pos, engine3D_vector3f_mulf(dir, amnt));
}

void engine3D_camera_rotateY(engine3D_camera_t *const camera, const float angleDeg) {
	engine3D_vector3f_t HAxis = engine3D_vector3f_normalized(engine3D_vector3f_cross(yAxis, camera->forward));
	camera->forward = engine3D_vector3f_normalized(engine3D_vector3f_rotateDeg(camera->forward, angleDeg, yAxis));
	camera->up = engine3D_vector3f_normalized(engine3D_vector3f_cross(camera->forward, HAxis));
}

void engine3D_camera_rotateX(engine3D_camera_t *const camera, const float angleDeg) {
	engine3D_vector3f_t HAxis = engine3D_vector3f_normalized(engine3D_vector3f_cross(yAxis, camera->forward));
	camera->forward = engine3D_vector3f_normalized(engine3D_vector3f_rotateDeg(camera->forward, angleDeg, HAxis));
	camera->up = engine3D_vector3f_normalized(engine3D_vector3f_cross(camera->forward, HAxis));
}

void engine3D_camera_left(const engine3D_camera_t *const camera, engine3D_vector3f_t *const left) {
	*left = engine3D_vector3f_cross(camera->forward, camera->up);
	engine3D_vector3f_normalize(left);
}

void engine3D_camera_right(const engine3D_camera_t *const camera, engine3D_vector3f_t *const right) {
	*right = engine3D_vector3f_cross(camera->up, camera->forward);
	engine3D_vector3f_normalize(right);
}
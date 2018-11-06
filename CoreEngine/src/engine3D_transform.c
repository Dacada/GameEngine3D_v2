#include <engine3D_transform.h>

#include <string.h>

engine3D_camera_t *engine3D_transform_camera;
float engine3D_transform_zNear;
float engine3D_transform_zFar;
float engine3D_transform_width;
float engine3D_transform_height;
float engine3D_transform_fov;

void engine3D_transform_reset(engine3D_transform_t *const transform) {
	transform->translation.x = 0;
	transform->translation.y = 0;
	transform->translation.z = 0;
	transform->rotation.x = 0;
	transform->rotation.y = 0;
	transform->rotation.z = 0;
	transform->scale.x = 1;
	transform->scale.y = 1;
	transform->scale.z = 1;
}

void engine3D_transform_getTransformation(const engine3D_transform_t *const transform, engine3D_matrix4f_t * const transformationMatrix) {
	engine3D_matrix4f_t translationMatrix, rotationMatrix, scaleMatrix, tmp;

	engine3D_matrix4f_setTranslation(&translationMatrix, transform->translation.x, transform->translation.y, transform->translation.z);
	engine3D_matrix4f_setRotation(&rotationMatrix, transform->rotation.x, transform->rotation.y, transform->rotation.z);
	engine3D_matrix4f_setScale(&scaleMatrix, transform->scale.x, transform->scale.y, transform->scale.z);

	engine3D_matrix4f_mul(&rotationMatrix, &scaleMatrix, &tmp);
	engine3D_matrix4f_mul(&translationMatrix, &tmp, transformationMatrix);
}

void engine3D_transform_getProjectedTransformation(const engine3D_transform_t *const transform, engine3D_matrix4f_t *const transformationMatrix) {
	engine3D_matrix4f_t projectionMatrix, cameraRotationMatrix, cameraTranslationMatrix, tmp1, tmp2;

	engine3D_transform_getTransformation(transform, transformationMatrix);
	engine3D_matrix4f_setProjection(&projectionMatrix, engine3D_transform_zNear, engine3D_transform_zFar, engine3D_transform_width, engine3D_transform_height, engine3D_transform_fov);
	engine3D_matrix4f_setCamera(&cameraRotationMatrix, engine3D_transform_camera->forward, engine3D_transform_camera->up);
	engine3D_matrix4f_setTranslation(&cameraTranslationMatrix, -engine3D_transform_camera->pos.x, -engine3D_transform_camera->pos.y, -engine3D_transform_camera->pos.z);

	engine3D_matrix4f_mul(&cameraTranslationMatrix, transformationMatrix, &tmp1);
	engine3D_matrix4f_mul(&cameraRotationMatrix, &tmp1, &tmp2);
	engine3D_matrix4f_mul(&projectionMatrix, &tmp2, transformationMatrix);
}
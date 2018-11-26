#include <engine3D_transform.h>

#include <string.h>

void engine3D_transform_reset(engine3D_transform_t *const transform) {
	transform->pos.x = 0;
	transform->pos.y = 0;
	transform->pos.z = 0;
	transform->rot.x = 0;
	transform->rot.y = 0;
	transform->rot.z = 0;
	transform->scale.x = 1;
	transform->scale.y = 1;
	transform->scale.z = 1;
}

void engine3D_transform_getTransformation(const engine3D_transform_t *const transform, engine3D_matrix4f_t * const transformationMatrix) {
	engine3D_matrix4f_t translationMatrix, rotationMatrix, scaleMatrix, tmp;

	engine3D_matrix4f_setTranslation(&translationMatrix, transform->pos.x, transform->pos.y, transform->pos.z);
	engine3D_matrix4f_setRotation(&rotationMatrix, transform->rot.x, transform->rot.y, transform->rot.z);
	engine3D_matrix4f_setScale(&scaleMatrix, transform->scale.x, transform->scale.y, transform->scale.z);

	engine3D_matrix4f_mul(&rotationMatrix, &scaleMatrix, &tmp);
	engine3D_matrix4f_mul(&translationMatrix, &tmp, transformationMatrix);
}

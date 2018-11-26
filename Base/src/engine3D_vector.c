#include <engine3D_vector.h>
#include <engine3D_util.h>

#include <math.h>
#include <string.h>

float engine3D_vector2f_length(const engine3D_vector2f_t v) {
	return sqrtf(v.x * v.x + v.y * v.y);
}

float engine3D_vector2f_dot(const engine3D_vector2f_t v1, const engine3D_vector2f_t v2) {
	return v1.x * v2.x + v1.y * v2.y;
}

engine3D_vector2f_t *engine3D_vector2f_normalize(engine3D_vector2f_t * const v) {
	float length = engine3D_vector2f_length(*v);
	v->x /= length;
	v->y /= length;
	return v;
}

engine3D_vector2f_t engine3D_vector2f_normalized(const engine3D_vector2f_t v) {
	engine3D_vector2f_t result;
	float length = engine3D_vector2f_length(v);
	result.x = v.x / length;
	result.y = v.y / length;
	return result;
}

engine3D_vector2f_t engine3D_vector2f_rotateRad(const engine3D_vector2f_t v, const float angle) {
	float c = cosf(angle);
	float s = sinf(angle);

	engine3D_vector2f_t result;

	result.x = v.x * c - v.y * s;
	result.y = v.x * s + v.y * c;

	return result;
}

engine3D_vector2f_t engine3D_vector2f_rotateDeg(const engine3D_vector2f_t v, const float angle) {
	return engine3D_vector2f_rotateRad(v, TO_RADIANS(angle));
}

engine3D_vector2f_t engine3D_vector2f_add(const engine3D_vector2f_t v1, const engine3D_vector2f_t v2) {
	engine3D_vector2f_t result;
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	return result;
}

engine3D_vector2f_t engine3D_vector2f_addf(const engine3D_vector2f_t v, const float f) {
	engine3D_vector2f_t result;
	result.x = v.x + f;
	result.y = v.y + f;
	return result;
}

engine3D_vector2f_t engine3D_vector2f_sub(const engine3D_vector2f_t v1, const engine3D_vector2f_t v2) {
	engine3D_vector2f_t result;
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	return result;
}

engine3D_vector2f_t engine3D_vector2f_subf(const engine3D_vector2f_t v, const float f) {
	engine3D_vector2f_t result;
	result.x = v.x - f;
	result.y = v.y - f;
	return result;
}

engine3D_vector2f_t engine3D_vector2f_mul(const engine3D_vector2f_t v1, const engine3D_vector2f_t v2) {
	engine3D_vector2f_t result;
	result.x = v1.x * v2.x;
	result.y = v1.y * v2.y;
	return result;
}

engine3D_vector2f_t engine3D_vector2f_mulf(const engine3D_vector2f_t v, const float f) {
	engine3D_vector2f_t result;
	result.x = v.x * f;
	result.y = v.y * f;
	return result;
}

engine3D_vector2f_t engine3D_vector2f_div(const engine3D_vector2f_t v1, const engine3D_vector2f_t v2) {
	engine3D_vector2f_t result;
	result.x = v1.x / v2.x;
	result.y = v1.y / v2.y;
	return result;
}

engine3D_vector2f_t engine3D_vector2f_divf(const engine3D_vector2f_t v, const float f) {
	engine3D_vector2f_t result;
	result.x = v.x / f;
	result.y = v.y / f;
	return result;
}

int engine3D_vector2f_fprintf(FILE *stream, const engine3D_vector2f_t v) {
	return fprintf(stream, "vector2d<%f,%f>\n", v.x, v.y);
}



float engine3D_vector3f_length(const engine3D_vector3f_t v) {
	return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

float engine3D_vector3f_dot(const engine3D_vector3f_t v1, const engine3D_vector3f_t v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

engine3D_vector3f_t engine3D_vector3f_cross(const engine3D_vector3f_t v1, const engine3D_vector3f_t v2) {
	engine3D_vector3f_t result;
	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;
	return result;
}

engine3D_vector3f_t *engine3D_vector3f_normalize(engine3D_vector3f_t * const v) {
	float length = engine3D_vector3f_length(*v);
	v->x /= length;
	v->y /= length;
	v->z /= length;
	return v;
}

engine3D_vector3f_t engine3D_vector3f_normalized(const engine3D_vector3f_t v) {
	engine3D_vector3f_t result;
	float length = engine3D_vector3f_length(v);
	result.x = v.x / length;
	result.y = v.y / length;
	result.z = v.z / length;
	return result;
}

engine3D_vector3f_t engine3D_vector3f_rotateRad(const engine3D_vector3f_t v, const float angle, const engine3D_vector3f_t axis) {
	engine3D_vector3f_t result;
	engine3D_quaternion_t rotation, rotationConj, w, tmp;

	float sinHalfAngle = sinf(angle / 2);
	float cosHalfAngle = cosf(angle / 2);

	rotation.x = axis.x * sinHalfAngle;
	rotation.y = axis.y * sinHalfAngle;
	rotation.z = axis.z * sinHalfAngle;
	rotation.w = cosHalfAngle;

	engine3D_quaternion_conjugate(&rotation, &rotationConj);
	
	engine3D_quaternion_mulv(&rotation, v, &tmp);
	engine3D_quaternion_mul(&tmp, &rotationConj, &w);

	result.x = w.x;
	result.y = w.y;
	result.z = w.z;

	return result;
}

engine3D_vector3f_t engine3D_vector3f_rotateDeg(const engine3D_vector3f_t v, const float angle, const engine3D_vector3f_t axis) {
	return engine3D_vector3f_rotateRad(v, TO_RADIANS(angle), axis);
}

engine3D_vector3f_t engine3D_vector3f_add(const engine3D_vector3f_t v1, const engine3D_vector3f_t v2) {
	engine3D_vector3f_t result;
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return result;
}

engine3D_vector3f_t engine3D_vector3f_addf(const engine3D_vector3f_t v, const float f) {
	engine3D_vector3f_t result;
	result.x = v.x + f;
	result.y = v.y + f;
	result.z = v.z + f;
	return result;
}

engine3D_vector3f_t engine3D_vector3f_sub(const engine3D_vector3f_t v1, const engine3D_vector3f_t v2) {
	engine3D_vector3f_t result;
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return result;
}

engine3D_vector3f_t engine3D_vector3f_subf(const engine3D_vector3f_t v, const float f) {
	engine3D_vector3f_t result;
	result.x = v.x - f;
	result.y = v.y - f;
	result.z = v.z - f;
	return result;
}

engine3D_vector3f_t engine3D_vector3f_mul(const engine3D_vector3f_t v1, const engine3D_vector3f_t v2) {
	engine3D_vector3f_t result;
	result.x = v1.x * v2.x;
	result.y = v1.y * v2.y;
	result.z = v1.z * v2.z;
	return result;
}

engine3D_vector3f_t engine3D_vector3f_mulf(const engine3D_vector3f_t v, const float f) {
	engine3D_vector3f_t result;
	result.x = v.x * f;
	result.y = v.y * f;
	result.z = v.z * f;
	return result;
}

engine3D_vector3f_t engine3D_vector3f_div(const engine3D_vector3f_t v1, const engine3D_vector3f_t v2) {
	engine3D_vector3f_t result;
	result.x = v1.x / v2.x;
	result.y = v1.y / v2.y;
	result.z = v1.z / v2.z;
	return result;
}

engine3D_vector3f_t engine3D_vector3f_divf(const engine3D_vector3f_t v, const float f) {
	engine3D_vector3f_t result;
	result.x = v.x / f;
	result.y = v.y / f;
	result.z = v.z / f;
	return result;
}

engine3D_vector3f_t engine3D_vector3f_abs(const engine3D_vector3f_t v) {
	engine3D_vector3f_t result;
	result.x = fabsf(v.x);
	result.y = fabsf(v.y);
	result.z = fabsf(v.z);
	return result;
}

int engine3D_vector3f_fprintf(FILE * stream, const engine3D_vector3f_t v) {
	return fprintf(stream, "vector2d<%f,%f,%f>\n", v.x, v.y, v.z);
}



void engine3D_matrix4f_setIdentity(engine3D_matrix4f_t * const matrix) {
	for (size_t i = 0; i < 4; i++) {
		for (size_t j = 0; j < 4; j++) {
			matrix->mat[i][j] = 0;
		}
		matrix->mat[i][i] = 1;
	}
}

void engine3D_matrix4f_setTranslation(engine3D_matrix4f_t * const matrix, float x, float y, float z) {
	engine3D_matrix4f_setIdentity(matrix);
	matrix->mat[0][3] = x;
	matrix->mat[1][3] = y;
	matrix->mat[2][3] = z;
}

void engine3D_matrix4f_setRotation(engine3D_matrix4f_t * const matrix, float x, float y, float z) {
	engine3D_matrix4f_t rx, ry, rz, tmp;

	engine3D_matrix4f_setIdentity(&rx);
	engine3D_matrix4f_setIdentity(&ry);
	engine3D_matrix4f_setIdentity(&rz);

	x = TO_RADIANS(x);
	y = TO_RADIANS(y);
	z = TO_RADIANS(z);

	rz.mat[0][0] =  cosf(z);
	rz.mat[0][1] = -sinf(z);
	rz.mat[1][0] =  sinf(z);
	rz.mat[1][1] =  cosf(z);

	rx.mat[1][1] =  cosf(x);
	rx.mat[1][2] = -sinf(x);
	rx.mat[2][1] =  sinf(x);
	rx.mat[2][2] =  cosf(x);

	ry.mat[0][0] =  cosf(y);
	ry.mat[0][2] = -sinf(y);
	ry.mat[2][0] =  sinf(y);
	ry.mat[2][2] =  cosf(y);

	engine3D_matrix4f_mul(&ry, &rx, &tmp);
	engine3D_matrix4f_mul(&rz, &tmp, matrix);
}

void engine3D_matrix4f_setScale(engine3D_matrix4f_t * const matrix, float x, float y, float z) {
	engine3D_matrix4f_setIdentity(matrix);
	matrix->mat[0][0] = x;
	matrix->mat[1][1] = y;
	matrix->mat[2][2] = z;
}

void engine3D_matrix4f_setPerspective(engine3D_matrix4f_t * const matrix, float zNear, float zFar, float aspectRatio, float fov) {
	float tanHalfFOV = tanf(fov / 2);
	float zRange = zNear - zFar;

	engine3D_matrix4f_setIdentity(matrix);
	matrix->mat[0][0] = 1.0f / (tanHalfFOV * aspectRatio);
	matrix->mat[1][1] = 1.0f / tanHalfFOV;
	matrix->mat[2][2] = (-zNear - zFar) / zRange;
	matrix->mat[3][2] = 1.0f;
	matrix->mat[2][3] = 2 * zFar * zNear / zRange;
	matrix->mat[3][3] = 0;
}

void engine3D_matrix4f_setOrthographic(engine3D_matrix4f_t * const matrix, float left, float right, float bottom, float top, float near, float far) {
  float width = right - left;
  float height = top - bottom;
  float depth = far - near;

  engine3D_matrix4f_setIdentity(matrix);
  matrix->mat[0][0] = 2/width;
  matrix->mat[0][3] = -(right + left)/width;
  matrix->mat[1][1] = 2/height;
  matrix->mat[1][3] = -(top + bottom)/height;
  matrix->mat[2][2] = -2/depth;
  matrix->mat[2][3] = -(far + near)/depth;
}

void engine3D_matrix4f_setCameraRotation(engine3D_matrix4f_t *const matrix, const engine3D_vector3f_t forward, const engine3D_vector3f_t up) {
	engine3D_vector3f_t f = engine3D_vector3f_normalized(forward);
	engine3D_vector3f_t r = engine3D_vector3f_normalized(up);

	r = engine3D_vector3f_cross(r, f);
	engine3D_vector3f_t u = engine3D_vector3f_cross(f, r);

	engine3D_matrix4f_setIdentity(matrix);
	matrix->mat[0][0] = r.x;
	matrix->mat[0][1] = r.y;
	matrix->mat[0][2] = r.z;
	matrix->mat[1][0] = u.x;
	matrix->mat[1][1] = u.y;
	matrix->mat[1][2] = u.z;
	matrix->mat[2][0] = f.x;
	matrix->mat[2][1] = f.y;
	matrix->mat[2][2] = f.z;
}

void engine3D_matrix4f_mul(const engine3D_matrix4f_t * const m1, const engine3D_matrix4f_t * const m2, engine3D_matrix4f_t * const r) {
	for (size_t i = 0; i < 4; i++) {
		for (size_t j = 0; j < 4; j++) {
			float sum = 0;
			for (size_t k = 0; k < 4; k++) {
				sum += m1->mat[i][k] * m2->mat[k][j];
			}
			r->mat[i][j] = sum;
		}
	}
}



float engine3D_quaternion_length(const engine3D_quaternion_t * const v) {
	return sqrtf(v->x * v->x + v->y * v->y + v->z * v->z + v->w * v->w);
}

engine3D_quaternion_t * engine3D_quaternion_normalize(engine3D_quaternion_t * const v) {
	float length = engine3D_quaternion_length(v);
	v->x /= length;
	v->y /= length;
	v->z /= length;
	v->w /= length;
	return v;
}

engine3D_quaternion_t * engine3D_quaternion_conjugate(const engine3D_quaternion_t * const v, engine3D_quaternion_t * const r) {
	r->x = -v->x;
	r->y = -v->y;
	r->z = -v->z;
	r->w = v->w;
	return r;
}

engine3D_quaternion_t * engine3D_quaternion_mul(const engine3D_quaternion_t * const v1, const engine3D_quaternion_t * const v2, engine3D_quaternion_t * const r) {
	r->w = v1->w * v2->w - v1->x * v2->x - v1->y * v2->y - v1->z * v2->z;
	r->x = v1->x * v2->w + v1->w * v2->x + v1->y * v2->z - v1->z * v2->y;
	r->y = v1->y * v2->w + v1->w * v2->y + v1->z * v2->x - v1->x * v2->z;
	r->z = v1->z * v2->w + v1->w * v2->z + v1->x * v2->y - v1->y * v2->x;
	return r;
}

engine3D_quaternion_t * engine3D_quaternion_mulv(const engine3D_quaternion_t * const v1, const engine3D_vector3f_t v2, engine3D_quaternion_t * const r) {
	r->w = -v1->x * v2.x - v1->y * v2.y - v1->z * v2.z;
	r->x =  v1->w * v2.x + v1->y * v2.z - v1->z * v2.y;
	r->y =  v1->w * v2.y + v1->z * v2.x - v1->x * v2.z;
	r->z =  v1->w * v2.z + v1->x * v2.y - v1->y * v2.x;
	return r;
}

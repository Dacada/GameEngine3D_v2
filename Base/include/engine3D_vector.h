#ifndef ENGINE3D_VECTOR_H
#define ENGINE3D_VECTOR_H

#include <stdio.h>
#include <stdbool.h>

// vector of 2 elements
typedef struct engine3D_vector2f_t {
	float x, y;
} engine3D_vector2f_t;

// vector length
float engine3D_vector2f_length(const engine3D_vector2f_t v);

// dot operation
float engine3D_vector2f_dot(const engine3D_vector2f_t v1, const engine3D_vector2f_t v2);

// cross product
float engine3D_vector2f_cross(const engine3D_vector2f_t v1, const engine3D_vector2f_t v2);

// normalize vector
engine3D_vector2f_t *engine3D_vector2f_normalize(engine3D_vector2f_t *const v);

// return normalized copy of vector
engine3D_vector2f_t engine3D_vector2f_normalized(const engine3D_vector2f_t v);

// rotate vector by given angle
engine3D_vector2f_t engine3D_vector2f_rotateRad(const engine3D_vector2f_t v, const float angle);

// sum operation 
engine3D_vector2f_t engine3D_vector2f_add(const engine3D_vector2f_t v1, const engine3D_vector2f_t v2);

// add a scalar to a vector
engine3D_vector2f_t engine3D_vector2f_addf(const engine3D_vector2f_t v, const float f);

// substraction operation
engine3D_vector2f_t engine3D_vector2f_sub(const engine3D_vector2f_t v1, const engine3D_vector2f_t v2);

// substract a scalar from a vector
engine3D_vector2f_t engine3D_vector2f_subf(const engine3D_vector2f_t v, const float f);

// multiplication operation
engine3D_vector2f_t engine3D_vector2f_mul(const engine3D_vector2f_t v1, const engine3D_vector2f_t v2);

// multiply a vectory by a scalar
engine3D_vector2f_t engine3D_vector2f_mulf(const engine3D_vector2f_t v, const float f);

// division operation
engine3D_vector2f_t engine3D_vector2f_div(const engine3D_vector2f_t v1, const engine3D_vector2f_t v2);

// divide a vector by a scalar
engine3D_vector2f_t engine3D_vector2f_divf(const engine3D_vector2f_t v, const float f);

// linear interpolation between two vectors
engine3D_vector2f_t engine3D_vector2f_lerp(const engine3D_vector2f_t v, const engine3D_vector2f_t dest, float lerp_factor);

// return whether two vectors are equal
bool engine3D_vector2f_equal(const engine3D_vector2f_t v1, const engine3D_vector2f_t v2);

// print a vector to given stream in a pretty way
int engine3D_vector2f_fprintf(FILE *stream, const engine3D_vector2f_t v);


// vector of 3 elements
typedef struct engine3D_vector3f_t {
	float x, y, z;
} engine3D_vector3f_t;

// vector length
float engine3D_vector3f_length(const engine3D_vector3f_t v);

// dot operation
float engine3D_vector3f_dot(const engine3D_vector3f_t v1, const engine3D_vector3f_t v2);

// cross product operation
engine3D_vector3f_t engine3D_vector3f_cross(const engine3D_vector3f_t v1, const engine3D_vector3f_t v2);

// normalize vector
engine3D_vector3f_t *engine3D_vector3f_normalize(engine3D_vector3f_t *const v);

// return normalized copy of vector
engine3D_vector3f_t engine3D_vector3f_normalized(const engine3D_vector3f_t v);

// rotate vector by given angle over given axis
engine3D_vector3f_t engine3D_vector3f_rotateRad(const engine3D_vector3f_t v, const float angle, const engine3D_vector3f_t axis);

// sum operation
engine3D_vector3f_t engine3D_vector3f_add(const engine3D_vector3f_t v1, const engine3D_vector3f_t v2);

// add a scalar to a vector
engine3D_vector3f_t engine3D_vector3f_addf(const engine3D_vector3f_t v, const float f);

// substraction operation
engine3D_vector3f_t engine3D_vector3f_sub(const engine3D_vector3f_t v1, const engine3D_vector3f_t v2);

// substract a scalar from a vector
engine3D_vector3f_t engine3D_vector3f_subf(const engine3D_vector3f_t v, const float f);

// multiplication operation
engine3D_vector3f_t engine3D_vector3f_mul(const engine3D_vector3f_t v1, const engine3D_vector3f_t v2);

// multiply a vectory by a scalar
engine3D_vector3f_t engine3D_vector3f_mulf(const engine3D_vector3f_t v, const float f);

// division operation
engine3D_vector3f_t engine3D_vector3f_div(const engine3D_vector3f_t v1, const engine3D_vector3f_t v2);

// divide a vector by a scalar
engine3D_vector3f_t engine3D_vector3f_divf(const engine3D_vector3f_t v, const float f);

// return a copy of a vector where each value is the absolute value
engine3D_vector3f_t engine3D_vector3f_abs(const engine3D_vector3f_t v);

// linear interpolation between two vectors
engine3D_vector3f_t engine3D_vector3f_lerp(const engine3D_vector3f_t v, const engine3D_vector3f_t dest, float lerp_factor);

// return whether two vectors are equal
bool engine3D_vector3f_equal(const engine3D_vector3f_t v1, const engine3D_vector3f_t v2);

// get xy component of vector
engine3D_vector2f_t engine3D_vector3f_xy(const engine3D_vector3f_t v);

// get yz component of vector
engine3D_vector2f_t engine3D_vector3f_yz(const engine3D_vector3f_t v);

// get xz component of vector
engine3D_vector2f_t engine3D_vector3f_xz(const engine3D_vector3f_t v);

// get yx component of vector
engine3D_vector2f_t engine3D_vector3f_yx(const engine3D_vector3f_t v);

// get zy component of vector
engine3D_vector2f_t engine3D_vector3f_zy(const engine3D_vector3f_t v);

// get zx component of vector
engine3D_vector2f_t engine3D_vector3f_zx(const engine3D_vector3f_t v);

// print a vector to given stream in a pretty way
int engine3D_vector3f_fprintf(FILE *stream, const engine3D_vector3f_t v);



// 4x4 matrix
typedef struct engine3D_matrix4f_t {
	float mat[4][4];
} engine3D_matrix4f_t;

// set matrix to the identity matrix
void engine3D_matrix4f_setIdentity(engine3D_matrix4f_t *const matrix);

// multiply two matrixes and save the result into a third
void engine3D_matrix4f_mul(const engine3D_matrix4f_t *const m1, const engine3D_matrix4f_t *const m2, engine3D_matrix4f_t *const r);

// set matrix to a translation matrix
void engine3D_matrix4f_setTranslation(engine3D_matrix4f_t * const matrix, float x, float y, float z);

// set matrix to a rotation matrix
void engine3D_matrix4f_setRotation(engine3D_matrix4f_t * const matrix, float x, float y, float z);

// set matrix to a scale matrix
void engine3D_matrix4f_setScale(engine3D_matrix4f_t * const matrix, float x, float y, float z);

// set matrix to a prespective projection
void engine3D_matrix4f_setPerspective(engine3D_matrix4f_t * const matrix, float zNear, float zFar, float aspectRatio, float fov);

// set matrix to an orthographic projection
void engine3D_matrix4f_setOrthographic(engine3D_matrix4f_t * const matrix, float left, float right, float bottom, float top, float near, float far);

// set matrix to a camera rotation matrix
void engine3D_matrix4f_setCameraRotation(engine3D_matrix4f_t * const matrix, const engine3D_vector3f_t forward, const engine3D_vector3f_t up);


// quaternion
typedef struct engine3D_quaternion_t {
  float x, y, z, w;
} engine3D_quaternion_t;

// get length of a quaternion
float engine3D_quaternion_length(const engine3D_quaternion_t *const v);

// normalize a quaternion inplace
engine3D_quaternion_t * engine3D_quaternion_normalize(engine3D_quaternion_t * const v);

// conjugate a quaternion and save it into another
engine3D_quaternion_t * engine3D_quaternion_conjugate(const engine3D_quaternion_t * const v, engine3D_quaternion_t * const r);

// multiply two quaternions and save it into a third
engine3D_quaternion_t * engine3D_quaternion_mul(const engine3D_quaternion_t * const v1, const engine3D_quaternion_t * const v2, engine3D_quaternion_t * const r);

// multiply a quaternion by a vector3f and save it into another quaternion
engine3D_quaternion_t * engine3D_quaternion_mulv(const engine3D_quaternion_t * const v1, const engine3D_vector3f_t v2, engine3D_quaternion_t * const r);

#endif /* ENGINE3D_VECTOR_H */

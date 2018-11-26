#ifndef ENGINE3D_CAMERA_H
#define ENGINE3D_CAMERA_H

#include <Base/engine3D_vector.h>
#include <Base/engine3D_transform.h>

// camera for prespective projection
typedef struct engine3D_camera_t {
  engine3D_vector3f_t pos;
  engine3D_vector3f_t forward;
  engine3D_vector3f_t up;
  engine3D_matrix4f_t *projection;
} engine3D_camera_t;

// initialzie camera
engine3D_camera_t *engine3D_camera_init(engine3D_camera_t *const camera, float fov, float aspect, float zNear, float zFar);

// normalize camera vectors
void engine3D_camera_normalize(engine3D_camera_t *const camera);

// get matrix for view projection for the camera
void engine3D_camera_getViewProjection(const engine3D_camera_t *const camera, engine3D_matrix4f_t *result);

// move camera in the given direction by given amount
void engine3D_camera_move(engine3D_camera_t *const camera, const engine3D_vector3f_t dir, const float amnt);

// rotate camera on X axis by given angle (radians)
void engine3D_camera_rotateX(engine3D_camera_t *const camera, const float angle);

// rotate camera on Y axis by given angle (radians)
void engine3D_camera_rotateY(engine3D_camera_t *const camera, const float angle);

void engine3D_camera_left(const engine3D_camera_t *const camera, engine3D_vector3f_t *const left);

void engine3D_camera_right(const engine3D_camera_t *const camera, engine3D_vector3f_t *const right);

// cleanup camera resources and deallocate memory
void engine3D_camera_cleanup(engine3D_camera_t *camera);

#endif /* ENGINE3D_CAMERA_H */

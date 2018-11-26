#ifndef DRAGCAMERAINPUT_H
#define DRAGCAMERAINPUT_H

#include <CoreEngine/engine3D_gameComponent.h>
#include <RenderingEngine/engine3D_camera.h>
#include <Base/engine3D_vector.h>
#include <stdbool.h>

// Component for dragging the camera to move it
typedef struct dragCameraInput_t {
  engine3D_gameComponent_t baseComponent;
  engine3D_vector2f_t centerPosition;
  engine3D_camera_t *camera;
  float sensitivity;
  bool movingCamera;
} dragCameraInput_t;

// create component, needs the reference to the camera and a sensitivity value
dragCameraInput_t *dragCameraInput_init(dragCameraInput_t *const dragCameraInput, engine3D_camera_t *camera, float sensitivity);

#endif /* DRAGCAMERAINPUT_H */

#ifndef DRAGCAMERAINPUT_H
#define DRAGCAMERAINPUT_H

#include <CoreEngine/engine3D_gameComponent.h>
#include <Base/engine3D_vector.h>
#include <stdbool.h>

typedef struct dragCameraInput_t {
  engine3D_gameComponent_t baseComponent;
  engine3D_vector2f_t centerPosition;
  bool movingCamera;
} dragCameraInput_t;

dragCameraInput_t *dragCameraInput_init(dragCameraInput_t *const dragCameraInput, float sensitivity);

#endif /* DRAGCAMERAINPUT_H */

#include <dragCameraInput.h>
#include <Base/engine3D_time.h>
#include <Base/engine3D_transform.h>
#include <RenderingEngine/engine3D_camera.h>
#include <CoreEngine/engine3D_input.h>

static void input(engine3D_gameComponent_t *component, double d) {
  dragCameraInput_t *dragCameraInput = (dragCameraInput_t*)component;
  float delta = (float)d;
  float movAmt = delta * 10;
  
  if (engine3D_input_getMouseDown(ENGINE3D_MOUSE_BUTTON_LEFT)) {
    engine3D_input_setCursor(ENGINE3D_CURSOR_DISABLED);
    engine3D_input_getMousePosition(&dragCameraInput->centerPosition);
    dragCameraInput->movingCamera = true;
  }
  
  if (engine3D_input_getMouseUp(ENGINE3D_MOUSE_BUTTON_LEFT)) {
    engine3D_input_setCursor(ENGINE3D_CURSOR_ENABLED);
    dragCameraInput->movingCamera = false;
  }
  
  if (engine3D_input_getKey(ENGINE3D_KEY_W)) {
    engine3D_camera_move(dragCameraInput->camera, dragCameraInput->camera->forward, movAmt);
  }
  if (engine3D_input_getKey(ENGINE3D_KEY_S)) {
    engine3D_camera_move(dragCameraInput->camera, dragCameraInput->camera->forward, -movAmt);
  }
  if (engine3D_input_getKey(ENGINE3D_KEY_A)) {
    engine3D_vector3f_t vec;
    engine3D_camera_left(dragCameraInput->camera, &vec);
    engine3D_camera_move(dragCameraInput->camera, vec, movAmt);
  }
  if (engine3D_input_getKey(ENGINE3D_KEY_D)) {
    engine3D_vector3f_t vec;
    engine3D_camera_right(dragCameraInput->camera, &vec);
    engine3D_camera_move(dragCameraInput->camera, vec, movAmt);
  }
  
  if (dragCameraInput->movingCamera) {
    engine3D_vector2f_t pos, deltaPos;
    engine3D_input_getMousePosition(&pos);
    deltaPos = engine3D_vector2f_sub(pos, dragCameraInput->centerPosition);
    
    if (deltaPos.x != 0) {
      engine3D_camera_rotateY(dragCameraInput->camera, deltaPos.x * dragCameraInput->sensitivity * delta);
    }
    
    if (deltaPos.y != 0) {
      engine3D_camera_rotateX(dragCameraInput->camera, deltaPos.y * dragCameraInput->sensitivity * delta);
    }
  }
}

dragCameraInput_t *dragCameraInput_init(dragCameraInput_t *const dragCameraInput, engine3D_camera_t *const camera, float s) {
  engine3D_gameComponent_init((engine3D_gameComponent_t*)dragCameraInput);
  dragCameraInput->baseComponent.input = &input;
  dragCameraInput->movingCamera = false;
  dragCameraInput->camera = camera;
  dragCameraInput->sensitivity = s;
  return dragCameraInput;
}

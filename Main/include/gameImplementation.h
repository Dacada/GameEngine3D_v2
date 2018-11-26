#ifndef GAMEIMPLEMENTATION_H
#define GAMEIMPLEMENTATION_H

#include <Base/engine3D_transform.h>
#include <RenderingEngine/engine3D_mesh.h>
#include <CoreEngine/engine3D_game.h>
#include <CoreEngine/engine3D_gameObject.h>
#include <CoreEngine/engine3D_core.h>
#include <RenderingEngine/engine3D_phongShader.h>
#include <RenderingEngine/engine3D_camera.h>
#include <RenderingEngine/engine3D_texture.h>
#include "meshRenderer.h"
#include "dragCameraInput.h"
#include "exitOnEsc.h"

// implementation of a game
typedef struct myGameImplementation {
  engine3D_game_t game; // base game object
  void(*parentInit)(struct engine3D_game_t*); // needed to be able to call the original's init method from the overridden init method
  engine3D_core_t *engine; // reference to the game engine we're using
  int width; // width of the screen
  int height; // height of the screen

  engine3D_camera_t *camera; // camera, to be freed later
  engine3D_material_t *material; // a material, to be freed later
  engine3D_texture_t *texture; // a texture, to be freed later
  engine3D_mesh_t *mesh; // a mesh, to be freed later
  engine3D_gameObject_t *planeObject; // an object, to be freed later
  meshRenderer_t *meshRenderer; // a component, to be freed later
  dragCameraInput_t *dragCameraInput; // a component, to be freed later
  exitOnEsc_t *exitOnEsc; // a component, to be freed later
} myGameImplementation;

// assign callbacks and create the game
void makeMyGameImplementation(myGameImplementation *game);

#endif /* GAMEIMPLEMENTATION_H */

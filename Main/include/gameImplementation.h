#ifndef GAMEIMPLEMENTATION_H
#define GAMEIMPLEMENTATION_H

#include <Base/engine3D_transform.h>
#include <RenderingEngine/engine3D_mesh.h>
#include <CoreEngine/engine3D_game.h>
#include <CoreEngine/engine3D_core.h>
#include <RenderingEngine/engine3D_phongShader.h>
#include <RenderingEngine/engine3D_camera.h>
#include <RenderingEngine/engine3D_texture.h>

typedef struct myGameImplementation {
  engine3D_game_t game;
  engine3D_core_t *engine;
  engine3D_mesh_t mesh;
  engine3D_phongShader_t shader;
  engine3D_transform_t transform;
  engine3D_material_t material;
  engine3D_camera_t camera;
  engine3D_texture_t texture;
  engine3D_vector3f_t color;
  int width;
  int height;
} myGameImplementation;

void makeMyGameImplementation(myGameImplementation *game);

#endif /* GAMEIMPLEMENTATION_H */

#include <gameImplementation.h>
#include <exitOnEsc.h>
#include <dragCameraInput.h>
#include <meshRenderer.h>
#include <Base/engine3D_util.h>
#include <RenderingEngine/engine3D_vertex.h>
#include <RenderingEngine/engine3D_mesh.h>
#include <RenderingEngine/engine3D_texture.h>
#include <CoreEngine/engine3D_input.h>

static void init(engine3D_game_t *g) {
  myGameImplementation *game = (myGameImplementation*)g;
  game->parentInit(g);
  
  engine3D_util_resourcesPath = "Main/res/";

  engine3D_camera_t *camera = engine3D_util_safeMalloc(sizeof(engine3D_camera_t));
  game->camera = camera;
  engine3D_camera_init(camera, TO_RADIANS(70.0f), game->width/game->height, 0.1f, 1000.0f);

  engine3D_material_t *material = engine3D_util_safeMalloc(sizeof(engine3D_material_t));
  game->material = material;
  engine3D_texture_t *texture = engine3D_util_safeMalloc(sizeof(engine3D_texture_t));
  game->texture = texture;
  *texture = engine3D_texture_loadFromFile("test.png");
  material->texture = texture;
  material->color.x = 1; material->color.y = 1; material->color.z = 1;
  material->specularIntensity = 1;
  material->specularPower = 1;

  engine3D_mesh_t *mesh = engine3D_util_safeMalloc(sizeof(engine3D_mesh_t));
  game->mesh = mesh;
  engine3D_mesh_init(mesh);
  float fieldDepth = 10;
  float fieldWidth = 10;
  engine3D_vertex_t vertices[] = { { {-fieldWidth,     0, -fieldDepth    },{0, 0},{0, 0, 0} },
				   { {-fieldWidth,     0,  fieldDepth * 3},{0, 1},{0, 0, 0} },
				   { { fieldWidth * 3, 0, -fieldDepth    },{1, 0},{0, 0, 0} },
				   { { fieldWidth * 3, 0,  fieldDepth * 3},{1, 1},{0, 0, 0} } };
  unsigned int indices[] = { 0,1,2, 2,1,3 };
  engine3D_mesh_addVertices(mesh, vertices, 4, indices, 6, true);

  meshRenderer_t *meshRenderer = engine3D_util_safeMalloc(sizeof(meshRenderer_t));
  game->meshRenderer = meshRenderer;
  meshRenderer_init(meshRenderer, mesh, material, camera);

  engine3D_gameObject_t *planeObject = engine3D_util_safeMalloc(sizeof(engine3D_gameObject_t));
  game->planeObject = planeObject;
  engine3D_gameObject_init(planeObject);
  engine3D_gameObject_addComponent(planeObject, (engine3D_gameComponent_t*)meshRenderer);
  planeObject->transform->pos.x = 0;
  planeObject->transform->pos.y = 0;
  planeObject->transform->pos.z = 0;

  engine3D_gameObject_addChild(g->root, planeObject);

  dragCameraInput_t *dragCameraInput = engine3D_util_safeMalloc(sizeof(dragCameraInput_t));
  game->dragCameraInput = dragCameraInput;
  dragCameraInput_init(dragCameraInput, camera, 0.5f);
  engine3D_gameObject_addComponent(g->root, (engine3D_gameComponent_t*)dragCameraInput);

  exitOnEsc_t *exitOnEsc = engine3D_util_safeMalloc(sizeof(exitOnEsc_t));
  game->exitOnEsc = exitOnEsc;
  exitOnEsc_init(exitOnEsc, game->engine);
  engine3D_gameObject_addComponent(g->root, (engine3D_gameComponent_t*)exitOnEsc);
}

static void cleanup(engine3D_game_t *g) {
  myGameImplementation *game = (myGameImplementation*)g;
  engine3D_gameObject_cleanup(game->game.root);
  
  free(game->planeObject);
  free(game->exitOnEsc);
  free(game->dragCameraInput);
  free(game->meshRenderer);
  free(game->mesh);
  free(game->texture);
  free(game->material);
  engine3D_camera_cleanup(game->camera);
  free(game->camera);
  free(game->game.root);
}

void makeMyGameImplementation(myGameImplementation *game) {
  engine3D_game_init((engine3D_game_t*)game);
  game->parentInit = game->game.init;
  game->game.init = &init;
  game->game.cleanup = &cleanup;
}

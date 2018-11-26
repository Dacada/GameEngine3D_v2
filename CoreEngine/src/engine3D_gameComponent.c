#include <engine3D_gameComponent.h>
#include <Base/engine3D_util.h>

static void nop(engine3D_gameComponent_t *const c) {
  UNUSED(c);
}

static void nop2(engine3D_gameComponent_t *const c, engine3D_shader_t *const s) {
  UNUSED(c);
  UNUSED(s);
}

engine3D_gameComponent_t *engine3D_gameComponent_init(engine3D_gameComponent_t *const gameComponent) {
  gameComponent->init = &nop;
  gameComponent->input = &nop;
  gameComponent->update = &nop;
  gameComponent->render = &nop2;
  gameComponent->cleanup = &nop;
  return gameComponent;
}

#include <exitOnEsc.h>
#include <CoreEngine/engine3D_core.h>
#include <CoreEngine/engine3D_input.h>

static void input(engine3D_gameComponent_t *component) {
  exitOnEsc_t *exitOnEsc = (exitOnEsc_t*)component;

  if (engine3D_input_getKey(ENGINE3D_KEY_ESCAPE)) {
    engine3D_core_stop(exitOnEsc->engine);
  }
}

exitOnEsc_t *exitOnEsc_init(exitOnEsc_t *const exitOnEsc, engine3D_core_t *const engine) {
  engine3D_gameComponent_init((engine3D_gameComponent_t*)exitOnEsc);
  exitOnEsc->baseComponent.input = &input;
  exitOnEsc->engine = engine;
  return exitOnEsc;
}

#ifndef EXITONESC_H
#define EXITONESC_H

#include <CoreEngine/engine3D_core.h>
#include <CoreEngine/engine3D_gameComponent.h>

// a component to exit when the esc key is pressed
typedef struct exitOnEsc_t {
  engine3D_gameComponent_t baseComponent;
  engine3D_core_t *engine;
} exitOnEsc_t;

// create the component, needs a reference to the engine in order to be able to stop it
exitOnEsc_t *exitOnEsc_init(exitOnEsc_t *const exitOnEsc, engine3D_core_t *const engine);

#endif /* EXITONESC_H */

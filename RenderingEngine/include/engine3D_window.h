#ifndef ENGINE3D_WINDOW_H
#define ENGINE3D_WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <stdbool.h>
#include <Base/engine3D_vector.h>

typedef GLFWwindow engine3D_window_t;

// Create the window. Bail on error.
engine3D_window_t *engine3D_window_create(const int width, const int height, const char *const title);

// Poll events and perform the framebuffer swap.
// If on debug mode, query for OpenGL errors.
void engine3D_window_update(engine3D_window_t *window);

// True if window must be closed.
bool engine3D_window_closeRequested(engine3D_window_t *window);

// get window size (x,y)
engine3D_vector2f_t engine3D_window_getSize(engine3D_window_t *window);

// get window's center coordinates (x,y)
engine3D_vector2f_t engine3D_window_getCenter(engine3D_window_t *window);

// Terminate and destroy the window.
void engine3D_window_destroy(engine3D_window_t *window);

#endif /* ENGINE3D_WINDOW_H */

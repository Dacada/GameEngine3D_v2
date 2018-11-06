#include <engine3D_input.h>
#include <engine3D_vector.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string.h>

#define LEN_KEYS (GLFW_KEY_LAST + 1)
#define LEN_MOUSE_BUTTONS (GLFW_MOUSE_BUTTON_LAST + 1)

GLFWwindow *engine3D_input_window = NULL;

static bool keys[LEN_KEYS];
static bool keysState[LEN_KEYS];
static bool keysDown[LEN_KEYS];
static bool keysUp[LEN_KEYS];

static bool mouseButtons[LEN_MOUSE_BUTTONS];
static bool mouseButtonsState[LEN_MOUSE_BUTTONS];
static bool mouseButtonsDown[LEN_MOUSE_BUTTONS];
static bool mouseButtonsUp[LEN_MOUSE_BUTTONS];

void engine3D_input_update(void) {
	for (int i = 0; i < LEN_KEYS; i++)
	{
		keysDown[i] = keys[i] && !keysState[i];
		keysUp[i] = !keys[i] && keysState[i];
	}
	memcpy(keysState, keys, sizeof(bool)*LEN_KEYS);

	for (int i = 0; i < LEN_MOUSE_BUTTONS; i++)
	{
		mouseButtonsDown[i] = mouseButtons[i] && !mouseButtonsState[i];
		mouseButtonsUp[i] = !mouseButtons[i] && mouseButtonsState[i];
	}
	memcpy(mouseButtonsState, mouseButtons, sizeof(bool)*LEN_MOUSE_BUTTONS);
}

bool engine3D_input_getKey(const engine3D_input_keyCode keyCode) {
	if (keyCode < 0 || keyCode > LEN_KEYS)
		return false;
	return keys[keyCode];
}

bool engine3D_input_getKeyDown(const engine3D_input_keyCode keyCode) {
	if (keyCode < 0 || keyCode > LEN_KEYS)
		return false;
	return keysDown[keyCode];
}

bool engine3D_input_getKeyUp(const engine3D_input_keyCode keyCode) {
	if (keyCode < 0 || keyCode > LEN_KEYS)
		return false;
	return keysUp[keyCode];
}

bool engine3D_input_getMouse(const engine3D_input_mouseButton mouseButton) {
	if (mouseButton < 0 || mouseButton > LEN_MOUSE_BUTTONS)
		return false;
	return mouseButtons[mouseButton];
}

bool engine3D_input_getMouseDown(const engine3D_input_mouseButton mouseButton) {
	if (mouseButton < 0 || mouseButton > LEN_MOUSE_BUTTONS)
		return false;
	return mouseButtonsDown[mouseButton];
}

bool engine3D_input_getMouseUp(const engine3D_input_mouseButton mouseButton) {
	if (mouseButton < 0 || mouseButton > LEN_MOUSE_BUTTONS)
		return false;
	return mouseButtonsUp[mouseButton];
}

void engine3D_input_getMousePosition(engine3D_vector2f_t *const position) {
	double x, y;
	glfwGetCursorPos(engine3D_input_window, &x, &y);
	position->x = (float)x;
	position->y = (float)y;
}

void engine3D_input_setMousePosition(const engine3D_vector2f_t *const position) {
	glfwSetCursorPos(engine3D_input_window, position->x, position->y);
}

void engine3D_input_setCursor(const engine3D_input_cursorMode mode) {
	switch (mode)
	{
	case ENGINE3D_CURSOR_ENABLED:
		glfwSetInputMode(engine3D_input_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		break;
	case ENGINE3D_CURSOR_HIDDEN:
		glfwSetInputMode(engine3D_input_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		break;
	case ENGINE3D_CURSOR_DISABLED:
		glfwSetInputMode(engine3D_input_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		break;
	}
}

void _engine3D_input_keyCallback(const GLFWwindow *const window, const int key, const int scancode, const int action, const int mods) {
	// Suppress unused warnings
	(void)window;
	(void)scancode;
	(void)mods;

	if (key < 0 || key > LEN_KEYS)
		return;
	keys[key] = action != GLFW_RELEASE;
}

void _engine3D_input_mouseButtonCallback(const GLFWwindow *const window, const int button, const int action, const int mods) {
	// Suppress unused warnings
	(void)window;
	(void)mods;

	if (button < 0 || button > LEN_MOUSE_BUTTONS)
		return;
	mouseButtons[button] = action != GLFW_RELEASE;
}

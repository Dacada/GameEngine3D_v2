#include <engine3D_input.h>
#include <Base/engine3D_vector.h>
#include <Base/engine3D_util.h>
#include <RenderingEngine/engine3D_window.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string.h>

#define LEN_KEYS (GLFW_KEY_LAST + 1)
#define LEN_MOUSE_BUTTONS (GLFW_MOUSE_BUTTON_LAST + 1)

engine3D_window_t *window;

bool keys[LEN_KEYS];
bool keysState[LEN_KEYS];
bool keysDown[LEN_KEYS];
bool keysUp[LEN_KEYS];

bool mouseButtons[LEN_MOUSE_BUTTONS];
bool mouseButtonsState[LEN_MOUSE_BUTTONS];
bool mouseButtonsDown[LEN_MOUSE_BUTTONS];
bool mouseButtonsUp[LEN_MOUSE_BUTTONS];

static void keyCallback(const engine3D_window_t *const w, const int key, const int scancode, const int action, const int mods) {
	UNUSED(scancode);
	UNUSED(mods);

#ifdef DEBUG
	if (w != window) {
		engine3D_util_debugPrint("warning: received keyboard input from unexpected window");
	}
#else
	UNUSED(w);
#endif

	if (key < 0 || key > LEN_KEYS) {
		engine3D_util_debugPrintf("warning: ignoring unexpected input keycode: %d", key);
		return;
	}
	keys[key] = action != GLFW_RELEASE;
}

static void mouseButtonCallback(const engine3D_window_t *const w, const int button, const int action, const int mods) {
	UNUSED(mods);

#ifdef DEBUG
	if (w != window) {
		engine3D_util_debugPrint("warning: received mouse button input from unexpected window");
	}
#else
	UNUSED(w);
#endif

	if (button < 0 || button > LEN_MOUSE_BUTTONS) {
		engine3D_util_debugPrintf("warning: ignoring unexpected input mousebutton: %d", button);
		return;
	}
	mouseButtons[button] = action != GLFW_RELEASE;
}

void engine3D_input_init(engine3D_window_t *const w) {
	window = w;
	glfwSetKeyCallback(w, (GLFWkeyfun)keyCallback);
	glfwSetMouseButtonCallback(w, (GLFWmousebuttonfun)mouseButtonCallback);
}

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
	glfwGetCursorPos(window, &x, &y);
	position->x = (float)x;
	position->y = (float)y;
}

void engine3D_input_setMousePosition(const engine3D_vector2f_t *const position) {
	glfwSetCursorPos(window, position->x, position->y);
}

void engine3D_input_setCursor(const engine3D_input_cursorMode mode) {
	switch (mode)
	{
	case ENGINE3D_CURSOR_ENABLED:
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		break;
	case ENGINE3D_CURSOR_HIDDEN:
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		break;
	case ENGINE3D_CURSOR_DISABLED:
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		break;
	}
}

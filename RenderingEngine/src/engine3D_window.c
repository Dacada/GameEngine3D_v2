#include <engine3D_window.h>
#include <engine3D_input.h>
#include <engine3D_util.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

#include <stdio.h>
#include <stdbool.h>

static GLFWwindow *window;
static const char *current_title;

#ifdef DEBUG
static void GLAPIENTRY debugMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam) {
	(void)userParam;

	switch (source) {
	case GL_DEBUG_SOURCE_API:
		printf("[API]");
		break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
		printf("[WINDOW SYSTEM]");
		break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER:
		printf("[SHADER COMPILER]");
		break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:
		printf("[THIRD PARTY]");
		break;
	case GL_DEBUG_SOURCE_APPLICATION:
		printf("[APPLICATION]");
		break;
	case GL_DEBUG_SOURCE_OTHER:
		printf("[OTHER]");
		break;
	default:
		printf("[UNKNOWN]");
		break;
	}

	switch (type) {
	case GL_DEBUG_TYPE_ERROR:
		printf("[ERROR]");
		break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		printf("[DEPRECATED BEHAVIOR]");
		break;
	case GL_DEBUG_SOURCE_API:
		printf("[API]");
		break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		printf("[UNDEFINED BEHAVIOR]");
		break;
	case GL_DEBUG_TYPE_PORTABILITY:
		printf("[PORTABILITY]");
		break;
	case GL_DEBUG_TYPE_PERFORMANCE:
		printf("[PERFORMANCE]");
		break;
	case GL_DEBUG_TYPE_MARKER:
		printf("[MARKER]");
		break;
	case GL_DEBUG_TYPE_PUSH_GROUP:
		printf("[PUSH GROUP]");
		break;
	case GL_DEBUG_TYPE_POP_GROUP:
		printf("[TYPE POP GROUP]");
		break;
	default:
		printf("[UNKNOWN]");
		break;
	}

	switch (severity) {
	case GL_DEBUG_SEVERITY_LOW:
		printf("[LOW]");
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		printf("[MEDIUM]");
		break;
	case GL_DEBUG_SEVERITY_HIGH:
		printf("[HIGH]");
		break;
	case GL_DEBUG_SEVERITY_NOTIFICATION:
		printf("[NOTIFICATION]");
		break;
	default:
		printf("[UNKNOWN]");
		break;
	}

	printf("[ID=%u]", id);

	printf(" - ");
	printf("%.*s", length, message);
	putchar('\n');
}
#endif

GLFWwindow *engine3D_window_create(const int width, const int height, const char *const title) {
	if (!glfwInit()) {
		engine3D_util_bail("failed to initialize glfw");
	}

#ifdef DEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif

	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (window == NULL) {
		engine3D_util_bail("failed to create glfw window");
	}
	current_title = title;

	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);
	glfwSetKeyCallback(window, (GLFWkeyfun)_engine3D_input_keyCallback);
	glfwSetMouseButtonCallback(window, (GLFWmousebuttonfun)_engine3D_input_mouseButtonCallback);

	if (glewInit() != GLEW_OK) {
		engine3D_util_bail("failed to initialize glew");
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

#ifdef DEBUG
	GLint flags;
	glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(debugMessage, NULL);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
	}
#endif

	return window;
}

void engine3D_window_update(void) {
#ifdef DEBUG
	engine3D_util_reportGlError();
#endif

	glfwPollEvents();
	glfwSwapBuffers(window);
}

bool engine3D_window_closeRequested(void) {
	return glfwWindowShouldClose(window);
}

void engine3D_window_getSize(int *const width, int *const height) {
	glfwGetFramebufferSize(window, width, height);
}

void engine3D_window_destroy(void) {
	glfwTerminate();
}

#include <Base/engine3D_util.h>
#include <engine3D_window.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <stdio.h>
#include <stdbool.h>

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

engine3D_window_t *engine3D_window_create(const int width, const int height, const char *const title) {
  if (!glfwInit()) {
    engine3D_util_bail("failed to initialize glfw");
  }
  
#ifdef DEBUG
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif
  
  engine3D_window_t *window = glfwCreateWindow(width, height, title, NULL, NULL);
  if (window == NULL) {
    engine3D_util_bail("failed to create glfw window");
  }
  
  glfwMakeContextCurrent(window);
  glfwSwapInterval(0);
  
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

void engine3D_window_update(engine3D_window_t *window) {
#ifdef DEBUG
  engine3D_util_reportGlError();
#endif

  glfwPollEvents();
  glfwSwapBuffers(window);
}

bool engine3D_window_closeRequested(engine3D_window_t *window) {
  return glfwWindowShouldClose(window);
}

engine3D_vector2f_t engine3D_window_getSize(engine3D_window_t *window) {
  engine3D_vector2f_t size;
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  size.x = width;
  size.y = height;
  return size;
}

engine3D_vector2f_t engine3D_window_getCenter(engine3D_window_t *window) {
  engine3D_vector2f_t center = engine3D_window_getSize(window);
  center.x /= 2;
  center.y /= 2;
  return center;
}

void engine3D_window_destroy(engine3D_window_t *window) {
  glfwDestroyWindow(window);
  glfwTerminate();
}

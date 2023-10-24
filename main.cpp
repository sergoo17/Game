#include <glad/egl.h>
#include <glad/gles2.h>

#define GLFW_INCLUDE_NONE 1
#include <GLFW/glfw3.h>

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#else
#define GLFW_EXPOSE_NATIVE_EGL 1
  #include <GLFW/glfw3native.h>
#endif

const GLuint WIDTH = 1920, HEIGHT = 1080;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void render_frame(GLFWwindow *window) {
    glfwPollEvents();

    glClearColor(0.7f, 0.9f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
}

int main() {
    if (!glfwInit())
        return -1;

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "GLFW", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

#ifndef __EMSCRIPTEN__
    EGLDisplay display = glfwGetEGLDisplay();
    gladLoaderLoadEGL(display);
#endif
    gladLoadGLES2(glfwGetProcAddress);

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg((em_arg_callback_func) render_frame, window, 60, 1);
#else
    while (!glfwWindowShouldClose(window)) { render_frame(window); }
#endif
    glfwTerminate();
    return 0;
}
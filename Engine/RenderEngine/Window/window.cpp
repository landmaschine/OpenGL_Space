#include "window.h"

void Window::createWindow(int width, int height) {
    _size.w = width;
    _size.h = height;

    window = glfwCreateWindow(_size.w, _size.h, "Space", NULL, NULL);
    if(window == NULL) {
        fmt::println("Error: Failed to create GLFW window: {:}", glfwGetError(NULL));
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);
}
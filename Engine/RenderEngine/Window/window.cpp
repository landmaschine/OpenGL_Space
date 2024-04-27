#include "window.h"

void Window::createWindow(int width, int height) {
    _size.w = width;
    _size.h = height;

    window = glfwCreateWindow(_size.w, _size.h, "Space", NULL, NULL);
    if(window == NULL) {
        std::cout << "Error: Failed to create GLFW window: " << glfwGetError(NULL) << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);
}
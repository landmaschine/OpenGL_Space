#include "window.h"

void Window::createWindow(int width, int height, std::string name) {
    m_size.w = width;
    m_size.h = height;

    m_window = glfwCreateWindow(m_size.w, m_size.h, name.c_str(), NULL, NULL);
    if(m_window == NULL) {
        std::cout << "Error: Failed to create GLFW window: " << glfwGetError(NULL) << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1);
}
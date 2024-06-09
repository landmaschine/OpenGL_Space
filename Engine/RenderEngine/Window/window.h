#pragma once
#include <GLFW/glfw3.h>
#include <iostream>

typedef struct windowSize {
    int w;
    int h;
} windowSize;

class Window {
    public:
        Window() = default;
        ~Window() {glfwDestroyWindow(m_window);}
        void createWindow(int width, int height, std::string name);
        windowSize& size() {return m_size;}
        GLFWwindow* getWin() { return m_window;}

    private:
        windowSize m_size;
        GLFWwindow* m_window;
};
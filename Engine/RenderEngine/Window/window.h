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
        ~Window() {glfwDestroyWindow(window);}
        void createWindow(int width, int height);
        windowSize& size() {return _size;}
        GLFWwindow* getWin() { return window;}

    private:
        windowSize _size;
        GLFWwindow* window;
};
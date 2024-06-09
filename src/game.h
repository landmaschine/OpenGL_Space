#pragma once
#include <GLFW/glfw3.h>

void init();
void shutDown();

void input();
void update(float dt);
void render(float alpha);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);


struct gameLoop {
    void run();
};
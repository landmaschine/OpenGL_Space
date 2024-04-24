#pragma once
#include <GLFW/glfw3.h>

void init();
void shutDown();

void input();
void update(float dt);
void render();

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void cusor_position_callback(GLFWwindow* window, double xpos, double ypos);

struct gameLoop {
    void run();
};

enum GAME_STATE {

};
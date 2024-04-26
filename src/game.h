#pragma once
#include <GLFW/glfw3.h>

void init();
void shutDown();

void input();
void update(float dt);
void render();

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

struct gameLoop {
    void run();
};

enum GAME_STATE {

};
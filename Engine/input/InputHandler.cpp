#include "InputHandler.h"
#include <GLFW/glfw3.h>

void InputHandler::update() {
    for (const auto& [key, command] : keyBindings) {
        if (glfwGetKey(window, key) == GLFW_PRESS) {
            command->pressed(*entity);
        }

        if (glfwGetKey(window, key) == GLFW_RELEASE) {
            command->released(*entity);
        }
    }
}

void InputHandler::shutdownKey() {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

bool InputHandler::shouldRenderHitbox() {
    if(glfwGetKey(window, GLFW_KEY_F3)) {
        return true;
    }
    return false;
}
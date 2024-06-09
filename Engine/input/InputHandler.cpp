#include "InputHandler.h"
#include <GLFW/glfw3.h>

void InputHandler::update() {
    for (const auto& [key, command] : m_keyBindings) {
        if (glfwGetKey(m_window, key) == GLFW_PRESS) {
            command->pressed(*m_entity);
        }

        if (glfwGetKey(m_window, key) == GLFW_RELEASE) {
            command->released(*m_entity);
        }
    }
}

void InputHandler::shutdownKey() {
    if(glfwGetKey(m_window, GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(m_window, GLFW_TRUE);
    }
}

bool InputHandler::shouldRenderHitbox() {
    if(glfwGetKey(m_window, GLFW_KEY_F3)) {
        return true;
    }
    return false;
}
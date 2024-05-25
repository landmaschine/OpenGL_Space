#pragma once
#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <GLFW/glfw3.h>
#include <memory>

#include "Command.h"

class InputHandler : public Command {
public:
    void update();

    void bindKey(int key, std::shared_ptr<Command> command) {
        keyBindings[key] = command;
    }

    void init(GLFWwindow* win, Entity& ent) {
        window = win;
        entity = &ent;
    }

    void shutdownKey();
    bool shouldRenderHitbox();

private:
    std::unordered_map<int, std::shared_ptr<Command>> keyBindings;
    GLFWwindow* window;
    Entity* entity;
};
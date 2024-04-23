#pragma once
#include <GLFW/glfw3.h>
#include <fmt/core.h>
#include <iostream>

#include "Engine/ECS/ECS.h"
#include "Engine/math/math.h"
#include "Engine/RenderEngine/Window/window.h"

class Movement {
    public:
        void calcTransform(glm::mat4& trans, glm::mat4& rotMat ,Window& _win, float dt, float& _mass, int& speedMod, glm::vec3& _vel, glm::vec2& _pos);
};
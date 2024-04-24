#pragma once
#include <GLFW/glfw3.h>
#define FMT_HEADER_ONLY
#include <fmt/core.h>
#include <iostream>

#include "Engine/ECS/ECS.h"
#include "Engine/math/math.h"
#include "Engine/RenderEngine/Window/window.h"

class Movement {
    public:
        void calcTransform(glm::mat4& trans, glm::mat4& rotMat ,Window& _win, float dt, float& _mass, 
                           int& speedMod, glm::vec3& _vel, glm::vec3& _pos, double xMousePos, double yMousePos);
    private:
        glm::vec3 extractTranslation(const glm::mat4& matrix) {
            return glm::vec3(matrix[3][0], matrix[3][1], matrix[3][2]);
        }

};
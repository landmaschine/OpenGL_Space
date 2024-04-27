#pragma once
#include <GLFW/glfw3.h>
#include <iostream>

#include "Engine/math/math.h"
#include "Engine/RenderEngine/Window/window.h"


namespace Physics {
    
    class Movement {
        public:
            glm::mat4 calcBehaviour(glm::mat4& trans, float dt, float& _mass, int& speedMod,
                                     glm::vec3& _vel, glm::vec3& _pos, double xMousePos, double yMousePos);

            void planetRotation(glm::mat4& trans, float dt);
        
        private:
            glm::vec3 extractTranslation(const glm::mat4& matrix) {
                return glm::vec3(matrix[3][0], matrix[3][1], 1.0f);
            }
    };

}
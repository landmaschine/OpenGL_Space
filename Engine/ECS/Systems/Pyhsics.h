#pragma once
#include <GLFW/glfw3.h>
#include <iostream>

#include "Engine/ECS/Components.h"

#include "Engine/math/math.h"
#include "Engine/RenderEngine/Window/window.h"

namespace Physics {
    class Movement {
        public:
            void calcBehaviour(MovementComponent* move, float dt);
        
        private:
            glm::vec3 extractTranslation(const glm::mat4& matrix) {
                return glm::vec3(matrix[3][0], matrix[3][1], matrix[3][2]);
            }
    };

    class PlanetRotation {
        public:
            void planetRotation(PlanetComponent* planet, float dt);
    };


    class Collision {
        public:
            static bool AABB(const collRect& recA, const collRect& recB, CollisionSide& side);
    };

}
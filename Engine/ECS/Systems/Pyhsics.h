#pragma once
#include <GLFW/glfw3.h>
#include <iostream>

#include "Engine/ECS/Components.h"

#include "Engine/math/math.h"
#include "Engine/RenderEngine/Window/window.h"

namespace Physics {
    class Movement : public Component{
        public:

            void init() override {
                if(!entity->hasComponent<MovementComponent>()) {
                    std::cout << "Player doesnt have PlayerMovementComponent!" << std::endl;
                }

                move = &entity->getComponent<MovementComponent>();

            };

            void update(float dt) override {
                move->finaltrans = calcBehaviour(dt);
            }
 
            glm::mat4 calcBehaviour(float dt);

            void planetRotation(glm::mat4& trans, float dt);
        
        private:
            MovementComponent* move;

            glm::vec3 extractTranslation(const glm::mat4& matrix) {
                return glm::vec3(matrix[3][0], matrix[3][1], matrix[3][2]);
            }
    };

    class Collision : public Component {
        public:
            static bool AABB();
        
        private:
    };

}
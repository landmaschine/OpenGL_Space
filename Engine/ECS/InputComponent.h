#pragma once
#include "ECS.h"
#include "PositionComponent.h"
#include "depComponents.h"

class InputComponent : public Component {
    public:
        InputComponent(playerData* data) {
            accelspeed = data->accelSpeed;
        }

        void update() override {
            force = direction * accelspeed * speedMod;
            if(entity->hasComponent<PositionComponent>()) {
                angle = std::atan2(mouseY, mouseX);
                rotmat = glm::rotate(glm::mat4(1.0f), angle + glm::radians(90.f), glm::vec3(0.0f, 0.0f, 1.0f));
                entity->getComponent<PositionComponent>().rota = rotmat;
            }
        }
        
        glm::vec2 direction = glm::vec2(0.0f);
        glm::vec2 force = glm::vec2(0.0f);
        glm::mat4 rotmat = glm::mat4(1.0f);
        float speedMod = 1;
        float accelspeed = 0;
        double mouseX;
        double mouseY;
        float angle;
};
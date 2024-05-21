#pragma once
#include "depComponents.h"
#include "PositionComponent.h"

class MovementComponent : public Component {
    public:
        MovementComponent(playerData* data) {
            pos = data->pos;
            maxSpeed = data->maxSpeed;  
            direction = glm::vec3(0.0f);
            velocity = glm::vec2(0.0f);
            trans = glm::mat4(1.0f);
            finaltrans = glm::mat4(1.0f);
            rota = glm::mat4(1.0f);
            mass = data->mass;
            speedMod = data->speedMod;
            accelSpeed = data->accelSpeed;
            acceleration = glm::vec4(1.0f);
        }

        MovementComponent() {
            pos = glm::vec3(1.0f);
            direction = glm::vec3(0.0f);
            velocity = glm::vec2(0.0f);
            trans = glm::mat4(1.0f);
            finaltrans = glm::mat4(1.0f);
            rota = glm::mat4(1.0f);
            mass = 2.f;
            speedMod = 1;
            acceleration = glm::vec4(1.0f);
        }

        void init() override {
            if(!entity->hasComponent<PositionComponent>()) {
                std::cout << "Entity has MovementComponent but no PositionComponent!" << std::endl;
            }
            trans = entity->getComponent<PositionComponent>().transform;
            entity->getComponent<PositionComponent>().rota = rota;
        }

        void update(float dt) override {
            entity->getComponent<PositionComponent>().transform = finaltrans;
            entity->getComponent<PositionComponent>().rota = rota;
        }

        glm::mat4 trans;
        glm::mat4 rota;
        glm::mat4 finalRota;
        glm::mat4 finaltrans;
        glm::vec3 pos;
        glm::vec3 direction;
        glm::vec2 velocity;
        float mass;
        glm::vec4 acceleration;
        int speedMod;
        double mouseX;
        double mouseY;
        float accelSpeed;
        double maxSpeed;
};
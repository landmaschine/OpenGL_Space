#pragma once
#include "Components.h"

class MovementComponent : public Component {
    public:
        void init() override {
            if(!entity->hasComponent<PositionComponent>()) {
                std::cout << "Entity has MovementComponent but no PositionComponent!" << std::endl;
            }
            pos = entity->getComponent<PositionComponent>().pos;

            direction = glm::vec3(0.0f);
            velocity = glm::vec2(0.0f);
            trans = glm::mat4(1.0f);
            finaltrans = glm::mat4(1.0f);
            rota = glm::mat4(1.0f);
            mass = 2.f;
            speedMod = 1;
            acceleration = glm::vec4(1.0f);
            trans = glm::rotate(trans, glm::radians(90.f), glm::vec3(1.0f, 0.0f, 0.0f));
        }

        void update(float dt) override {
            entity->getComponent<PositionComponent>().pos = pos;
            entity->getComponent<PositionComponent>().transform = finaltrans;
        }

        void datainit() {
            scale = entity->getComponent<PositionComponent>().scale;

            std::cout << scale << std::endl;
            trans = glm::translate(trans, pos);
            trans = glm::scale(trans, glm::vec3(scale));
        }

        glm::mat4 trans;
        glm::mat4 rota;
        glm::mat4 finaltrans;
        glm::vec3 pos;
        glm::vec3 direction;
        glm::vec2 velocity;
        float mass;
        glm::vec4 acceleration;
        double scale;
        int speedMod;
        double mouseX;
        double mouseY;
        float accelSpeed;
        double maxSpeed;
};
#pragma once
#include "Components.h"

class MovementComponent : public Component {
    public:
        void init() override {
            pos = glm::vec3(0.0f, 0.0f, 0.0f);
            direction = glm::vec3(0.0f);
            velocity = glm::vec2(0.0f);
            trans = glm::mat4(1.0f);
            finaltrans = glm::mat4(1.0f);
            rota = glm::mat4(1.0f);
            mass = 2.f;
            speedMod = 1;
            scale = .3f;
            trans = glm::scale(trans, glm::vec3(scale));
            trans = glm::translate(trans, pos);
            trans = glm::rotate(trans, -glm::radians(90.f), glm::vec3(1.0f, 0.0f, 0.0f));
        }

        void update(float dt) override {
            entity->getComponent<PositionComponent>().pos = pos;
            entity->getComponent<PositionComponent>().transform = finaltrans;
            pos.z = 0.0f;
        }

        glm::mat4 trans;
        glm::mat4 rota;
        glm::mat4 finaltrans;
        glm::vec3 pos;
        glm::vec3 direction;
        glm::vec2 velocity;
        float mass;
        float scale;
        int speedMod;
        double mouseX;
        double mouseY;

    private:
};
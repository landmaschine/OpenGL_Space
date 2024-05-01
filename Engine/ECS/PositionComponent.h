#pragma once
#include "Components.h"

class PositionComponent : public Component {
    public:
        void init() override {
            pos = glm::vec3(1.0f, 1.0f, -10.f);
            transform = glm::mat4(1.0f);
            transform = glm::translate(transform, pos);
            transform = glm::scale(transform, glm::vec3(1.0f));
        }

        void update(float dt) override {
        }

        glm::vec3 pos;
        glm::mat4 transform;

        int height = 32;
        int widht = 32;
        int scale = 1;
};
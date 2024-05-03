#pragma once
#include "Components.h"


class PositionComponent : public Component {
    public:
        PositionComponent() {}
        PositionComponent(float x, float y, float z) {
            pos.x = x;
            pos.y = y;
            pos.z = z;
        }


        void init() override {
            transform = glm::mat4(1.0f);
        }

        void update(float dt) override {
            
        }

        void datainit() {
            transform = glm::translate(transform, pos);
            transform = glm::scale(transform, glm::vec3(scale));
        }

        glm::vec3 pos;
        glm::mat4 transform;
        double scale;
};
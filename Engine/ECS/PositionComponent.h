#pragma once
#include "Components.h"

class PositionComponent : public Component {
    public:
        PositionComponent() {
            pos = glm::vec3(1.0f);
            transform = glm::mat4(1.0f);
            scale = 1;
        }

        PositionComponent(float x, float y, background* data) {
            pos.x = x;
            pos.y = y;
            pos.z = data->posz;
            scale = data->scale;
        }

        PositionComponent(playerData* data) {
            pos = data->pos;
            scale = data->scale;
        }

        void init() override {
            width = 0;
            height = 0;
            transform = glm::mat4(1.0f);
            transform = glm::translate(transform, pos);
            transform = glm::scale(transform, glm::vec3(scale));
        }

        void update(float dt) override {
            
        }

        glm::vec3 pos;
        glm::mat4 transform;
        double scale;
        int width, height;
};
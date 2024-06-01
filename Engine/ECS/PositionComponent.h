#pragma once
#include "depComponents.h"

class PositionComponent : public Component {
    public:
        PositionComponent() {
            pos = glm::vec3(0.0f);
            prevPos = glm::vec3(0.0f);
            transform = glm::mat4(1.0f);
            rota = glm::mat4(1.0f);
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

        PositionComponent(colliderData* data) {
            pos = data->pos;
            scale = data->scale;
        }

        void init() override {
            width = 0;
            height = 0;
            prevPos = pos;
            transform = glm::mat4(1.0f);
            transform = glm::translate(transform, pos);
            transform = glm::scale(transform, glm::vec3(scale));
        }

        void update() override {
            transform = glm::mat4(1.0f);
            transform = glm::translate(transform, pos);
        }

        glm::vec3 pos;
        glm::vec3 prevPos;
        glm::mat4 transform;
        glm::mat4 rota;
        double scale;
        int width, height;
};
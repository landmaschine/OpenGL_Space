#pragma once
#include "Components.h"

typedef struct rect {
    float w = 1.f;
    float h = 1.f;
    double scale = 1;
    glm::vec3 pos;
} collRect;

enum class CollisionSide {
    None,
    Horizontal,
    Vertical,
    Both
};

class CollisionComponent : public Component {
    public:
        CollisionComponent(playerData* data) {
            rect.scale = data->scale;
            rect.w *= rect.scale;
            rect.h *= rect.scale;
            rect.pos.x = data->pos.x - rect.w / 2;
            rect.pos.y = data->pos.y - rect.h / 2;
        }

        CollisionComponent(float x, float y, background* data) {
            pos = glm::vec3(x, y, data->posz);
            rect.scale = data->scale;
            rect.pos = pos;
            rect.h *= rect.scale;
            rect.w *= rect.scale;

            rect.pos.x = pos.x - rect.w / 2;
            rect.pos.y = pos.y - rect.h / 2;
        }

        void init() override {
            
        }

        void update(float dt) override {
            rect.pos = entity->getComponent<PositionComponent>().pos;
            rect.pos.x = entity->getComponent<PositionComponent>().pos.x - rect.w / 2;
            rect.pos.y = entity->getComponent<PositionComponent>().pos.y - rect.h / 2;
        }

        std::string tag;
        collRect rect;
    private:
        glm::vec3 pos;
        Shader shader;
};
#pragma once
#include "Components.h"

typedef struct rect {
    float w = 2.f;
    float h = 2.f;
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
        void init() override {
            if(!entity->hasComponent<PositionComponent>()) {
                entity->addComponent<PositionComponent>();
            } else {
                rect.pos = entity->getComponent<PositionComponent>().pos;
            }
        }

        void update(float dt) override {
            rect.pos = entity->getComponent<PositionComponent>().pos;
        }

        void datainit() {
            rect.w *= entity->getComponent<PositionComponent>().scale;
            rect.h *= entity->getComponent<PositionComponent>().scale;
        }

        std::string tag;
        collRect rect;
    private:
};
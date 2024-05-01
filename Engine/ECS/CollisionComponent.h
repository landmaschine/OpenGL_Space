#pragma once
#include "Components.h"

typedef struct rect {
    float width = 1.f;
    float height = 1.f;
    PositionComponent* pos;
} collRect;

class CollisionComponent : public Component {
    public:
        void init() override {
            if(!entity->hasComponent<PositionComponent>()) {
                entity->addComponent<PositionComponent>();
            } else {
                rect.pos = &entity->getComponent<PositionComponent>();
            }
        }

        void update(float dt) override {
            rect.pos = &entity->getComponent<PositionComponent>();
            std::cout << rect.pos->pos.x << " : " << rect.pos->pos.y << std::endl;
        }

        std::string tag;
    private:
        collRect rect;
};
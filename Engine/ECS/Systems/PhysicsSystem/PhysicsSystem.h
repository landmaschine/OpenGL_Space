#pragma once
#include "Engine/ECS/ECS.h"
#include "Engine/PhysicsEngine/Pyhsics.h"

class PhysicsSystem : public System {
    public:
        void update(std::vector<std::unique_ptr<Entity>>& entities, float dt) override {
            for(auto& e : entities) {
                if(e->hasComponent<PhysicsComponent>()) {
                    physics.physicsSim(&e->getComponent<PhysicsComponent>(), dt);
                }
            }
        }

    private:
        Physics physics;
};
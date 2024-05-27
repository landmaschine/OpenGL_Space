#pragma once
#include "Engine/ECS/ECS.h"
#include "Engine/PhysicsEngine/Pyhsics.h"

class PhysicsSystem : public System {
    public:
        PhysicsSystem(int numSteps) : numSteps(numSteps) {}

        void update(float dt, std::vector<std::unique_ptr<Entity>>& entities) override {
            for(auto& e : entities) {
                if(e->hasComponent<PhysicsComponent>()) {
                    for(int i = 0; i < numSteps; ++i) {
                        physics.physicsSim(&e->getComponent<PhysicsComponent>(), dt);
                        std::cout << e->getComponent<PhysicsComponent>().body.currentPos.x << std::endl;
                    }
                }
            }
        }

    private:
        Physics::Physics physics;
        int numSteps;
};
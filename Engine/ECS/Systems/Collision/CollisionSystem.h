#pragma once
#include <vector>
#include "Engine/ECS/ECS.h"
#include "Engine/ECS/CollisionComponent/CollisionComponentPoly.h"
#include "Engine/ECS/MovementComponent.h"
#include "Engine/PhysicsEngine/Pyhsics.h"

class CollisionSystem : public System {
    public:
        void update(float dt, std::vector<std::unique_ptr<Entity>>& entities) override;
    private:
        Physics::CollisionInfo collinfo;
};
#pragma once
#include <vector>
#include "Engine/ECS/ECS.h"
#include "Engine/ECS/CollisionComponentPoly.h"
#include "Engine/PhysicsEngine/Pyhsics.h"

class CollisionSystem : public System {
    public:
        void update(std::vector<std::unique_ptr<Entity>>& entities, float dt) override;
    private:
        CollisionInfo m_collinfo;
};
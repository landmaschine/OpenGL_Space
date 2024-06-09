#pragma once
#include <GLFW/glfw3.h>
#include <iostream>

#include "RigidBody.h"
#include "Engine/ECS/depComponents.h"

#include "Engine/math/math.h"
#include "Engine/Tools/utils.h"
#include "Engine/RenderEngine/Window/window.h"

#include "Engine/ECS/CollisionComponentPoly.h"
#include "Engine/ECS/PositionComponent.h"
#include "Engine/ECS/PlanetComponent.h"
#include "Engine/ECS/PhysicsComponent.h"

struct CollisionInfo {
    bool hasCollision;
    glm::vec2 collisionNormal;
    float penetrationDepth;
};

class Physics {
    public:
        void physicsSim(PhysicsComponent* phys, float dt);
    private:
        void applyVerletIntegration(RigidBody& body, float dt);
        void applyForce(RigidBody& body);
        void applyRotationVerletIntegration(RigidBody& body, float torque, float dt);
        void applyTorque(RigidBody& body, float torque);
};

class Collision {
    public:
        bool EPA(const std::vector<glm::vec2>& poly1, const std::vector<glm::vec2>& poly2, std::vector<glm::vec2>& simplex, CollisionInfo& collisionInfo);
        void HandleCollision_Player(PhysicsComponent& move, const glm::vec2& collisionNormal);
        bool CheckCollision(const PolyData& obj1, const PolyData& obj2, CollisionInfo& collisionInfo);
    private:
        glm::vec2 Support(const std::vector<glm::vec2>& poly1, const std::vector<glm::vec2>& poly2, const glm::vec2& direction);
        bool GJK(const std::vector<glm::vec2>& poly1, const std::vector<glm::vec2>& poly2, std::vector<glm::vec2>& simplex);
        bool SameDirection(const glm::vec2& direction, const glm::vec2& ao);
        glm::vec2 TripleProduct(const glm::vec2& a, const glm::vec2& b, const glm::vec2& c);
};
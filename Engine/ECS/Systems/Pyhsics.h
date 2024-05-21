#pragma once
#include <GLFW/glfw3.h>
#include <iostream>

#include "Engine/ECS/depComponents.h"

#include "Engine/math/math.h"
#include "Engine/Tools/utils.h"
#include "Engine/RenderEngine/Window/window.h"

#include "Engine/ECS/CollisionComponent/CollisionComponentPoly.h"
#include "Engine/ECS/MovementComponent.h"
#include "Engine/ECS/PositionComponent.h"
#include "Engine/ECS/PlanetComponent.h"

namespace Physics {
    namespace CollInfo {
        struct CollisionInfo {
            bool hasCollision;
            glm::vec2 collisionNormal;
            float penetrationDepth;
        };
    }

    class Movement {
        public:
            void calcBehaviour(MovementComponent* move, float dt);
    };

    class PlanetRotation {
        public:
            void planetRotation(PlanetComponent* planet, float dt);
    };

    class Collision {
        public:
            

            bool EPA(const std::vector<glm::vec2>& poly1, const std::vector<glm::vec2>& poly2, std::vector<glm::vec2>& simplex, CollInfo::CollisionInfo& collisionInfo);
            void HandleCollision_Player(MovementComponent& move, const glm::vec2& collisionNormal);
            bool CheckCollision(const PolyData& obj1, const PolyData& obj2, CollInfo::CollisionInfo& collisionInfo);
        private:
            glm::vec2 Support(const std::vector<glm::vec2>& poly1, const std::vector<glm::vec2>& poly2, const glm::vec2& direction);
            bool GJK(const std::vector<glm::vec2>& poly1, const std::vector<glm::vec2>& poly2, std::vector<glm::vec2>& simplex);
            bool SameDirection(const glm::vec2& direction, const glm::vec2& ao);
            glm::vec2 TripleProduct(const glm::vec2& a, const glm::vec2& b, const glm::vec2& c);
    };
}
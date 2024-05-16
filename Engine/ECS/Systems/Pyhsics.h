#pragma once
#include <GLFW/glfw3.h>
#include <iostream>

#include "Engine/ECS/depComponents.h"

#include "Engine/math/math.h"
#include "Engine/RenderEngine/Window/window.h"

#include "Engine/ECS/CollisionComponent/CollisionComponentPoly.h"
#include "Engine/ECS/MovementComponent.h"
#include "Engine/ECS/PositionComponent.h"
#include "Engine/ECS/PlanetComponent.h"
#include "Engine/ECS/CollisionComponent.h"


namespace Physics {
    class Movement {
        public:
            void calcBehaviour(MovementComponent* move, float dt);
        
        private:
            glm::vec3 extractTranslation(const glm::mat4& matrix) {
                return glm::vec3(matrix[3][0], matrix[3][1], matrix[3][2]);
            }
    };

    class PlanetRotation {
        public:
            void planetRotation(PlanetComponent* planet, float dt);
    };


    class Collision {
        public:
            static bool AABB(const collRect& recA, const collRect& recB, CollisionSide& side);
            void HandleCollision_Player(MovementComponent& move, CollisionSide& side);
            
            bool CheckCollision(const std::vector<glm::vec2>& polygon1, const std::vector<glm::vec2>& polygon2);
        private:
            glm::vec2 CalculateEdgeNormal(const glm::vec2& p1, const glm::vec2& p2);
            void ProjectPolygon(const std::vector<glm::vec2>& polygon, const glm::vec2& axis, float& minProjection, float& maxProjection);
            bool Overlap(float min1, float max1, float min2, float max2);
            
    };
}
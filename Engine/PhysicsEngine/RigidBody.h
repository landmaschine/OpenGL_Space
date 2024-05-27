#pragma once
#include "Engine/math/math.h"

struct RigidBody {
        glm::vec2 currentPos;
        glm::vec2 previousPos;
        glm::vec4 acceleration;
        float damping;

        bool isStatic;
        bool isAwake;

        void Mass(float mass) {
            mass = mass > 0 ? 1.0f / mass : 0.0f;
        }

        float Mass() {
            return mass;
        }

        float invMass() {
            return inverseMass;
        }

        private:
            float mass;
            float inverseMass;
    };
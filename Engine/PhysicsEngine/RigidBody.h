#pragma once
#include "Engine/math/math.h"

struct RigidBody {
    glm::mat4 rotmat = glm::mat4(1.0f);
    glm::mat4 inverserotmat = glm::mat4(1.0f);
    glm::vec2 currentPos = glm::vec2(0.0f);
    glm::vec2 previousPos = glm::vec2(0.0f);
    glm::vec2 acceleration = glm::vec2(0.0f);
    glm::vec2 velocity = glm::vec2(0.0f);
    glm::vec2 force = glm::vec2(0.0f);
    float currentAngle = 0.f;
    float previousAngle = 0.f;
    float angularAcceleration = 0.f;
    float angularVelocity = 0.f;
    float mass = 0.f;
    float inertia = 0.f;
    float damping = 0.f;
    float angularDamping = 0.f;
    bool isAwake;
    bool isStatic;

    float Mass() const { return mass; }
    float Inertia() const { return inertia; }
};
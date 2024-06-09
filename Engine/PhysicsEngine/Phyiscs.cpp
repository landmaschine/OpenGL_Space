#include "Pyhsics.h"

void Physics::physicsSim(PhysicsComponent* phys, float dt) {
   if (!phys->body.isStatic && phys->body.isAwake) {
        applyForce(phys->body);
        applyTorque(phys->body, phys->torque);
        applyVerletIntegration(phys->body, dt);
        applyRotationVerletIntegration(phys->body, phys->torque, dt);
        phys->body.acceleration = glm::vec2(0.0f, 0.0f);
        phys->body.angularAcceleration = 0.0f;
    }
}

void Physics::applyForce(RigidBody& body) {
    if (!body.isStatic && body.isAwake) {
        glm::vec4 force = glm::vec4(body.force, 0.f, 0.f) * body.inverserotmat;
        body.force.x = force.x;
        body.force.y = force.y; 

        body.acceleration += body.force / body.Mass();
    }
}

void Physics::applyTorque(RigidBody& body, float torque) {
    if (!body.isStatic && body.isAwake) {
        body.angularAcceleration += torque / body.Inertia();
    }
}

void Physics::applyVerletIntegration(RigidBody& body, float dt) {
    if (!body.isStatic && body.isAwake) {
        glm::vec2 newPos = body.currentPos + body.velocity * dt + 0.5f * body.acceleration * dt * dt;
        glm::vec2 newVelocity = body.velocity + 0.5f * (body.acceleration + (body.force / body.Mass())) * dt;
        body.previousPos = body.currentPos;
        body.currentPos = newPos;
        body.velocity = newVelocity;
        body.velocity *= body.damping;
    }
}

void Physics::applyRotationVerletIntegration(RigidBody& body, float torque, float dt) {
    if (!body.isStatic && body.isAwake) {
        float newAngle = body.currentAngle + body.angularVelocity * dt + 0.5f * body.angularAcceleration * dt * dt;

        float newAngularVelocity = body.angularVelocity + 0.5f * (body.angularAcceleration + (torque / body.Inertia())) * dt;

        body.previousAngle = body.currentAngle;
        body.currentAngle = newAngle;
        body.angularVelocity = newAngularVelocity;
    }
}


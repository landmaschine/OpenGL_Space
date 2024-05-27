#include "Pyhsics.h"

void Physics::Physics::physicsSim(PhysicsComponent* phys, float dt) {
    applyUserInputForce(phys);
    applyForce(phys->body, phys->force);
    applyVerletIntegration(phys->body, dt); 
}

void Physics::Physics::applyForce(RigidBody& body, const glm::vec2& force) {
    if (body.isAwake == true) {
        body.acceleration += glm::vec4(force / body.Mass(), 0.0f, 0.0f);
        std::cout << "he\n";
    }
}

void Physics::Physics::applyUserInputForce(PhysicsComponent* phys) {
    glm::vec2 userForce(0.0f, 0.0f);
    if(phys->direction().x == 1) {
        userForce.x += phys->accelSpeed();
    }

    applyForce(phys->body, userForce);
}

void Physics::Physics::applyVerletIntegration(RigidBody& body, float dt) {
    if (!body.isStatic && body.isAwake) {
        glm::vec2 temp = body.currentPos;
        glm::vec2 velocity = (body.currentPos - body.previousPos) * body.damping;
        body.currentPos += velocity + glm::vec2(body.acceleration) * (dt * dt);
        body.previousPos = temp;
    }
}
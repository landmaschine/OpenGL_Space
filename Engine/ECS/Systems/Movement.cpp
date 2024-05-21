#include "Pyhsics.h"

void Physics::Movement::calcBehaviour(MovementComponent* move, float dt) {
    float cursorangle = glm::atan(move->mouseY, move->mouseX);
    move->rota = glm::rotate(move->rota, cursorangle + glm::radians(90.f), glm::vec3(0.0f, 0.0f, 1.0f));

    static glm::vec2 acceleration = glm::vec2(0.0f);
    float friction = 0;

    glm::vec2 direction_norm(move->direction.x, move->direction.y);
    if (!(direction_norm.x == 0 && direction_norm.y == 0)) {
        direction_norm = glm::normalize(direction_norm);
        move->acceleration = glm::vec4(move->accelSpeed * move->speedMod * direction_norm.x / move->mass, 
                                       move->accelSpeed * move->speedMod * direction_norm.y / move->mass, 
                                       0.0f , 0.0f);
        
        move->acceleration = move->rota * move->acceleration;
        acceleration = glm::vec2(move->acceleration.x * 4, move->acceleration.y * 4) * dt;

        move->velocity += acceleration;

        float speed = glm::length(move->velocity);
        if(speed > move->maxSpeed) {
            move->velocity = glm::normalize(move->velocity) * glm::vec2(move->maxSpeed);
        }

    } else {
        float velMag = glm::length(move->velocity);
        if (velMag > 0.001f) {
            friction = (10.f * static_cast<float>(move->speedMod) * (velMag / 4) / move->mass) * dt;
            move->velocity -= glm::normalize(move->velocity) * friction;
        } else {
            move->velocity = glm::vec2(0.0f);
        }
    }
    move->trans = glm::translate(move->trans, glm::vec3(move->velocity.x * dt, move->velocity.y * dt,  move->pos.z));

    glm::mat4 tmp = glm::mat4(1.0f);
    tmp = move->trans * move->rota;
    move->trans = glm::translate(move->trans, glm::vec3(move->velocity.x * dt, move->velocity.y * dt, -move->pos.z));

    move->finaltrans = tmp;
    move->finalRota = move->rota;

    move->rota = glm::rotate(move->rota, -cursorangle - glm::radians(90.f), glm::vec3(0.0f, 0.0f, 1.0f));
    move->pos = utils::extractTranslation(move->trans);
}

void Physics::PlanetRotation::planetRotation(PlanetComponent* planet, float dt) {
    float rotateAngle = .1f * dt;
    planet->rotMat = glm::rotate(planet->rotMat, rotateAngle, glm::vec3(0.0f, 1.0f, 1.0f));
}
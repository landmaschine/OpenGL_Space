#include "Pyhsics.h"

glm::mat4 Physics::Movement::calcBehaviour(float dt) {
    float cursorangle = glm::atan(move->mouseY, move->mouseX);
    move->rota = glm::rotate(move->rota, -cursorangle + glm::radians(90.f), glm::vec3(0.0f, 1.0f, 0.0f));

    static glm::vec2 acceleration = glm::vec2(0.0f);
    float friction = 0;

    glm::vec2 direction_norm(move->direction.x, move->direction.y);
    if (!(direction_norm.x == 0 && direction_norm.y == 0)) {
        direction_norm = glm::normalize(direction_norm);
        glm::vec4 acceleration4 = glm::vec4(10.f * move->speedMod * direction_norm.x / move->mass, 0.0f, 10.f * move->speedMod * direction_norm.y / move->mass, 0.0f);
        acceleration4 = move->rota * acceleration4;
        acceleration = glm::vec2(acceleration4.x * 4, acceleration4.z * 4) * dt;

        move->velocity += acceleration;
    } else {
        float velMag = glm::length(move->velocity);
        if (velMag > 0.001f) {
            friction = (10.f * static_cast<float>(move->speedMod) * (velMag / 4) / move->mass) * dt;
            move->velocity -= glm::normalize(move->velocity) * friction;
        } else {
            move->velocity = glm::vec2(0.0f);
        }
    }

    move->trans = glm::translate(move->trans, glm::vec3(move->velocity.x * dt, move->pos.z, move->velocity.y * dt));
    glm::mat4 tmp = glm::mat4(1.0f);
    tmp = move->trans * move->rota;
    move->trans = glm::translate(move->trans, glm::vec3(move->velocity.x * dt, -move->pos.z, move->velocity.y * dt));

    move->rota = glm::rotate(move->rota, cursorangle - glm::radians(90.f), glm::vec3(0.0f, 1.0f, 0.0f));
    move->pos = extractTranslation(move->trans);

    return tmp;
}

void Physics::Movement::planetRotation(glm::mat4& trans, float dt) {
    float rotateAngle = .1f * dt;
    trans = glm::rotate(trans, rotateAngle, glm::vec3(0.0f, 1.0f, 1.0f));
}
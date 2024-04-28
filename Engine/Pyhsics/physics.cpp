#include "physics.h"

glm::mat4 Physics::Movement::calcBehaviour(glm::mat4& trans, glm::mat4& rota, float dt, float& _mass, int& speedMod, 
                                           glm::vec3& direction, glm::vec3& _pos, glm::vec2& velocity, double xMousePos, double yMousePos) {
    
    float cursorangle = glm::atan(yMousePos, xMousePos);
    rota = glm::rotate(rota, -cursorangle + glm::radians(90.f), glm::vec3(0.0f, 1.0f, 0.0f));

    static glm::vec2 acceleration = glm::vec2(0.0f);
    float friction = 0;

    glm::vec2 direction_norm(direction.x, direction.y);
    if (!(direction_norm.x == 0 && direction_norm.y == 0)) {
        direction_norm = glm::normalize(direction_norm);
        glm::vec4 acceleration4 = glm::vec4(20.f * speedMod * direction_norm.x / _mass, 0.0f, 20.f * speedMod * direction_norm.y / _mass, 0.0f);
        acceleration4 = rota * acceleration4;
        acceleration = glm::vec2(acceleration4.x * 4, acceleration4.z * 4) * dt;

        velocity += acceleration;
    } else {
        float velMag = glm::length(velocity);
        if(velMag > 0.001f) {
            friction = (10.f * static_cast<float>(speedMod) * (velMag / 4) / _mass) * dt;
            velocity -= glm::normalize(velocity) * friction;
        } else {
            velocity = glm::vec2(0.0f);
        }
    }

    trans = glm::translate(trans, glm::vec3(velocity.x * dt, 0.0f, velocity.y * dt));
    glm::mat4 tmp = glm::mat4(1.0f);
    tmp = trans * rota;
    
    rota = glm::rotate(rota, cursorangle - glm::radians(90.f), glm::vec3(0.0f, 1.0f, 0.0f));
    _pos = extractTranslation(trans);

    return tmp;
}


void Physics::Movement::planetRotation(glm::mat4& trans, float dt) {
    float rotateAngle = .1f * dt;
    trans = glm::rotate(trans, rotateAngle, glm::vec3(0.0f, 1.0f, 1.0f));
}
#include "physics.h"

void Movement::calcTransform(glm::mat4& trans, glm::mat4& rotMat, Window& _win, float dt, float& _mass, int& speedMod, glm::vec3& _vel, glm::vec3& _pos, double xMousePos, double yMousePos) {
    float deltaX = xMousePos - _pos.x;
    float deltaY = yMousePos - _pos.y;
    float cursorangle = glm::atan(deltaY, deltaX);

    trans = glm::translate(trans, _vel * glm::vec3(1.f * dt * speedMod, 1.f * dt * speedMod, 0.0f));

    rotMat = glm::translate(glm::mat4(1.0f), glm::vec3(glm::vec2(0, 0), 0.0f)) *
             glm::rotate(glm::mat4(1.0f), cursorangle, glm::vec3(0.0f, 0.0f, 1.0f)) *
             glm::translate(glm::mat4(1.0f), glm::vec3(glm::vec2(0, 0), 0.0f));

    _pos += _vel * glm::vec3(1.f * dt * speedMod, 1.f * dt * speedMod, 0.0f);

    //fmt::print("x: {:}", _pos.x);
    //fmt::println(" y: {:}", _pos.y);
}

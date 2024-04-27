#include "physics.h"

glm::mat4 Physics::Movement::calcBehaviour(glm::mat4& trans, float dt, float& _mass, int& speedMod, 
                                            glm::vec3& _vel, glm::vec3& _pos, double xMousePos, double yMousePos) {

    float cursorangle = atan2(yMousePos, xMousePos);

    glm::mat4 tmp = trans;
    trans = glm::rotate(trans, cursorangle - glm::radians(90.f), glm::vec3(0.0f, 0.0f, 1.0f));
    trans = tmp = glm::translate(trans, glm::vec3(_vel.x * 5.f * speedMod * dt , _vel.y * 5.f * speedMod * dt, 0.0f));
    _pos = extractTranslation(trans);

    trans = glm::rotate(trans, -cursorangle + glm::radians(90.f), glm::vec3(0.0f, 0.0f, 1.0f));
    return tmp;
}
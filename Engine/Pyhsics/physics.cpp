#include "physics.h"

void Movement::calcTransform(glm::mat4& trans, glm::mat4& rotMat, Window& _win, float dt, float& _mass, int& speedMod, glm::vec3& _vel, glm::vec3& _pos) {
    double x = 0;
    double y = 0;
    glfwGetCursorPos(_win.getWin(), &x, &y);
    float centerX = _win.size().w / 2.0f;
    float centerY = _win.size().h / 2.0f;
    float deltaX = x - centerX;
    float deltaY = y - centerY;
    glm::vec2 dirVec = glm::vec2(deltaX, deltaY);

    float cursorangle = atan2(dirVec.y, dirVec.x);
    std::cout << deltaX << " : " << deltaY << std::endl;

    trans = glm::translate(trans, _vel * glm::vec3(1.f * dt * speedMod, 1.f * dt * speedMod, 0.0f));
    rotMat = glm::rotate(glm::mat4(1.0f), -cursorangle, glm::vec3(0.0f, 0.0f, 1.0f));
}

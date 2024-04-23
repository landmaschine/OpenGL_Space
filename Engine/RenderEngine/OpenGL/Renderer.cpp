#include "Renderer.h"

void Renderer::render() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::setProjectionOrto() {
    orto = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, -100.0f, 100.0f);
    shader.setMat4("projection", orto);
}

void Renderer::setProjectionPers() {
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)800/(float)600, 0.1f, 100.0f);
    shader.setMat4("projection", proj);
}
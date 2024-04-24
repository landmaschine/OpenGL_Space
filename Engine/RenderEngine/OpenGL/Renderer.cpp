#include "Renderer.h"

void Renderer::render() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::setProjectionOrto(Window& window) {
    glUseProgram(shaderID());
    orto = glm::ortho(-window.size().w / 2.f, window.size().w / 2.f, window.size().h / 2.f, -window.size().h / 2.f, -100.0f, 100.0f);
    shader.setMat4("projection", orto);
}

void Renderer::setProjectionPers(Window& window) {
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)window.size().w/(float)window.size().h, 0.1f, 100.0f);
    shader.setMat4("projection", proj);
}
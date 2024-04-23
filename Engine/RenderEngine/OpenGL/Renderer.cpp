#include "Renderer.h"
#include <glad/glad.h>

void Renderer::render() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::setProjectionOrto() {
    orto = glm::ortho(-400.0f, 400.0f, -300.0f, 300.0f, -100.0f, 100.0f);
    shader.setMat4("projection", orto);
}

void Renderer::setProjectionPers() {

}
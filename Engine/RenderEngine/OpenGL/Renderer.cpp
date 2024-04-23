#include "Renderer.h"
#include <glad/glad.h>

void Renderer::render() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::setProjectionOrto() {
    shader.setMat4("view", view);
    shader.setMat4("projection", orto);
}

void Renderer::setProjectionPers() {

}
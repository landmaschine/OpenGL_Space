#include "HitBoxRender.h"

HitBoxRender::HitBoxRender() : VAO(0), VBO(0), EBO(0) {}

void HitBoxRender::init(PolyData poly) {
    shader.loadShader("/home/leonw/Documents/dev/OpenGL_Space/Engine/ECS/CollisionComponent/vertexShader.vs",
                      "/home/leonw/Documents/dev/OpenGL_Space/Engine/ECS/CollisionComponent/fragmentShader.fs");

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    shader.use();
}

HitBoxRender::~HitBoxRender() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void HitBoxRender::render(glm::mat4 view, glm::mat4 projection, glm::mat4 transform) {
    shader.use();
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);
    shader.setMat4("model", transform);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void HitBoxRender::setpolygons(PolyData polygons) {
    this->polygons = polygons;
    vertices = polydata.createVertecis(polygons);
    indices = polydata.createIndices(polygons);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
}
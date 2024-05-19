#include "HitBoxRender.h"

HitBoxRender::HitBoxRender() {}

HitBoxRender::HitBoxRender(PolyData poly) {
    polydat.print(poly);
    shader.loadShader("/home/leonw/Documents/dev/OpenGL_Space/Engine/ECS/CollisionComponent/vertexShader.vs",
                      "/home/leonw/Documents/dev/OpenGL_Space/Engine/ECS/CollisionComponent/fragmentShader.fs");
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    shader.use();
}

HitBoxRender::~HitBoxRender() {
    
}

void HitBoxRender::render(Icamer2D& cam, PositionComponent& pos) {
    shader.use();
    shader.setMat4("view", cam.view());
    shader.setMat4("projection", cam.projection());
    shader.setMat4("model", pos.transform);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
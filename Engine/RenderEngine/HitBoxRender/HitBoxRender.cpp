#include "HitBoxRender.h"

HitBoxRender::HitBoxRender() : VAO(0), m_VBO(0), m_EBO(0) {
    hitboxShader.loadShader("/home/leonw/Documents/dev/OpenGL_Space/Engine/RenderEngine/HitBoxRender/hitboxVertex.vs",
                            "/home/leonw/Documents/dev/OpenGL_Space/Engine/RenderEngine/HitBoxRender/hitboxFragment.fs");
}

void HitBoxRender::init() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), m_vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

HitBoxRender::~HitBoxRender() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
}

void HitBoxRender::setpolygons(PolyData polygons) {
    m_polygons = polygons;
    m_vertices = m_polydata.createVertecis(polygons);
    indices = m_polydata.createIndices(polygons);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), m_vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
}
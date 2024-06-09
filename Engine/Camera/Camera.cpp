#include "Camera.h"

void Camera2D::updatePosition(glm::vec3 playerPosition, Window& window) {
    glm::vec2 playerScreenPos = glm::vec2(playerPosition.x + window.size().w, playerPosition.y + window.size().h);

    m_screenWidth = window.size().w;
    m_screenHeight = window.size().h;

    m_position.x = playerScreenPos.x - m_screenWidth;
    m_position.y = playerScreenPos.y - m_screenHeight;

    updateViewMatrix();
    updateProjectionMatrixOrto();
}

void Camera2D::setZoom(float newZoom) {
    m_zoom = newZoom;
    updateProjectionMatrixOrto();
}

void Camera2D::window(Window& win) {
    m_window = win;
}

glm::mat4 Camera2D::getViewMatrix() const {
    return m_viewMatrix;
}

glm::mat4 Camera2D::getProjectionMatrix() {
    updateProjectionMatrixOrto();
    return m_projectionMatrix;
}

glm::mat4 Camera2D::projection() {
    return m_projectionMatrix;
}

glm::mat4 Camera2D::view() {
    return m_viewMatrix;
}

void Camera2D::updateViewMatrix() {
    m_viewMatrix = glm::lookAt(glm::vec3(m_position.x, m_position.y, m_zoom),
                   glm::vec3(m_position.x, m_position.y, m_position.z),
                   glm::vec3(0.0f, 1.0f, 0.0f));   
    m_shaderCam.setMat4("view", m_viewMatrix);
}

void Camera2D::updateProjectionMatrixOrto() {
    float zoomFactor = 1.0f / m_zoom;
    float halfScreenWidth = (float)m_screenWidth * 0.5f;
    float halfScreenHeight = (float)m_screenHeight * 0.5f;
    float left = -halfScreenWidth * zoomFactor;
    float right = halfScreenWidth * zoomFactor;
    float bottom = -halfScreenHeight * zoomFactor;
    float top = halfScreenHeight * zoomFactor;
    m_projectionMatrix = glm::ortho(left, right, bottom, top, -10000.0f, 10000.0f);
    m_shaderCam.setMat4("projection", m_projectionMatrix);
}

void Camera2D::updateProjectionMatrixPers(float fov) {
    m_projectionMatrix = glm::perspective(glm::radians(fov), m_screenWidth / float(m_screenHeight), -10.f, 10.f);
    m_shaderCam.setMat4("projection", m_projectionMatrix);
}

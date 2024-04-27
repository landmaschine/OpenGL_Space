#pragma once
#include "Engine/math/math.h"
#include "Engine/RenderEngine/Window/window.h"

class Camera2D {
    public:
        void init(Window& win) {
            this->screenHeight = win.size().h;
            this->screenWidth = win.size().w;
            position = glm::vec3(1.0f);
            zoom = 100.0f;
            updateProjectionMatrix();
        }

        void updatePosition(glm::vec3 playerPosition, Window& window) {
            glm::vec2 playerScreenPos = glm::vec2(playerPosition.x + window.size().w, playerPosition.y + window.size().h);

            screenWidth = window.size().w;
            screenHeight = window.size().h;

            position.x = playerScreenPos.x - screenWidth;
            position.y = playerScreenPos.y - screenHeight;

            updateViewMatrix();
        }

        void setZoom(float newZoom) {
            zoom = newZoom;
            fmt::println("zoomm {:}", zoom);
            updateProjectionMatrix();
        }

        void window(Window& win) {
            _window = win;
        }

        glm::mat4 getViewMatrix() const {
            return viewMatrix;
        }

        glm::mat4 getProjectionMatrix() {
            updateProjectionMatrix();
            return projectionMatrix;
        }

    private:
        void updateViewMatrix() {
            viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-position.x, -position.y, 0.0f));
        }

        void updateProjectionMatrix() {
            float zoomFactor = 1.0f / zoom;
            float halfScreenWidth = (float)screenWidth * 0.5f;
            float halfScreenHeight = (float)screenHeight * 0.5f;
            float left = -halfScreenWidth * zoomFactor;
            float right = halfScreenWidth * zoomFactor;
            float bottom = -halfScreenHeight * zoomFactor;
            float top = halfScreenHeight * zoomFactor;
            projectionMatrix = glm::ortho(left, right, bottom, top, -100.0f, 100.0f);
        }

        glm::mat4 viewMatrix;
        glm::mat4 projectionMatrix;
        glm::vec3 position;
        Window _window;
        float zoom = 1.0f;
        int screenWidth = 0;
        int screenHeight = 0;
};
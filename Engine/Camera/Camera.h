#pragma once
#include "Engine/math/math.h"
#include "Engine/RenderEngine/Window/window.h"

class Camera2D {
    public:
        void init(Window& win) {
            this->screenHeight = win.size().h;
            this->screenWidth = win.size().w;
            position = glm::vec3(1.0f);
            zoom = 1.0f;
            updateProjectionMatrix();
        }

        void updatePosition(glm::vec3 playerPosition, Window& window) {
            position.x = playerPosition.x - window.size().w / (2.0f * zoom);
            position.y = playerPosition.y - window.size().h / (2.0f * zoom);
            updateViewMatrix();
        }

        void setZoom(float newZoom) {
            zoom = newZoom;
            updateProjectionMatrix();
        }

        void window(Window& win) {
            _window = win;
        }

        glm::mat4 getViewMatrix() const {
            return viewMatrix;
        }

        glm::mat4 getProjectionMatrix() const {
            return projectionMatrix;
        }

    private:
        void updateViewMatrix() {
            viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-position.x, -position.y, 0.0f));
            fmt::print("viewX {:}", -position.x);
            fmt::println("viewY {:}", -position.y);
        }

        void updateProjectionMatrix() {
            projectionMatrix = glm::ortho(0.f, (float)screenWidth, 0.f, (float)screenHeight, -100.0f, 100.0f);
        }

        glm::mat4 viewMatrix;
        glm::mat4 projectionMatrix;
        glm::vec3 position;
        Window _window;
        float zoom = 0.5;
        int screenWidth = 0;
        int screenHeight = 0;
};
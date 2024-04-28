#pragma once
#include "Engine/math/math.h"
#include "Engine/RenderEngine/Window/window.h"

class Icamer2D {
    public:
        virtual glm::mat4 projection() = 0;
        virtual glm::mat4 view() = 0;
};

class Camera2D : public Icamer2D {
    public:
        void init(Window& win) {
            this->screenHeight = win.size().h;
            this->screenWidth = win.size().w;
            position = glm::vec3(1.0f);
            zoom = 100.0f;

            shader.loadShader("/home/leonw/Documents/dev/OpenGL_Space/Engine/RenderEngine/Shaders/shaderfiles/vertex.vs",
                              "/home/leonw/Documents/dev/OpenGL_Space/Engine/RenderEngine/Shaders/shaderfiles/fragment.fs");

            updateProjectionMatrix();
        }

        void updatePosition(glm::vec3 playerPosition, Window& window) {
            glm::vec2 playerScreenPos = glm::vec2(playerPosition.x + window.size().w, playerPosition.y + window.size().h);

            screenWidth = window.size().w;
            screenHeight = window.size().h;

            position.x = playerScreenPos.x - screenWidth;
            position.y = playerScreenPos.y - screenHeight;

            updateViewMatrix();
            updateProjectionMatrix();
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

        glm::mat4 getProjectionMatrix() {
            updateProjectionMatrix();
            return projectionMatrix;
        }

        glm::mat4 projection() override {
            return projectionMatrix;
        }

        glm::mat4 view() override {
            return viewMatrix;
        }

    private:
        void updateViewMatrix() {
            viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-position.x, -position.y, 0.0f));
            shader.setMat4("view", viewMatrix);
        }

        void updateProjectionMatrix() {
            float zoomFactor = 1.0f / zoom;
            float halfScreenWidth = (float)screenWidth * 0.5f;
            float halfScreenHeight = (float)screenHeight * 0.5f;
            float left = -halfScreenWidth * zoomFactor;
            float right = halfScreenWidth * zoomFactor;
            float bottom = -halfScreenHeight * zoomFactor;
            float top = halfScreenHeight * zoomFactor;
            projectionMatrix = glm::ortho(left, right, bottom, top, -10000.0f, 10000.0f);
            shader.setMat4("projection", projectionMatrix);
        }

        glm::mat4 viewMatrix;
        glm::mat4 projectionMatrix;
        glm::vec3 position;
        Window _window;
        float zoom = 1.0f;
        int screenWidth = 0;
        int screenHeight = 0;
        Shader shader;
};